#include "WordInfo.h"
#include <iterator>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

WordInfo::WordInfo()
{
}

void WordInfo::ReadWordsFromFile(const char* filename)
{
  std::ifstream infile(filename);
  std::string line;
  while (getline(infile, line))
  {
    std::vector<char> striped_line;
    for (char character : line)
    {
      const int char_int = int(character);
      if ((65 <= char_int && char_int < 91) || (97 <= char_int && char_int < 123) || char_int == 32 || char_int == 45)
        striped_line.push_back(char_int);
    }

    std::string line_str(striped_line.begin(), striped_line.end());
    std::transform(line_str.begin(), line_str.end(), line_str.begin(), ::tolower);


    std::istringstream iss(line_str);
    std::vector<std::string> result{
      std::istream_iterator<std::string>(iss),{}
    };

    for (const std::string& word : result)
    {
      m_total_words += 1;
      if (m_words_to_count.find(word) != m_words_to_count.end())
      {
        m_words_to_count[word] += 1;
      }
      else
        m_words_to_count[word] = 1;
    }
  }
}

void WordInfo::DisplayStats() const
{
  std::cout << "Total number of words : " << m_total_words << std::endl;
  std::cout << "Number of unique words : " << m_words_to_count.size() << std::endl;
  std::cout << "Average word length : " << GetAvgWordSize() << std::endl;
  std::cout << "Longest word : " << GetLongestWord() << std::endl;
  //Total number of words : 2364
  //  Number of unique words : 620
  //  Average word length : 3
  //  Longest word : pocket - handkerchief
  //  3 most frequent words :
  //the 96
  //  and 86
  //  a 74
  //  3 most frequent words(ignoring most commonly used) :
  //  his 48
  //  said 27
  //  my 26
  //  Longest word(s) :
  //  pocket - handkerchief
  //  Enter a word for an exact search :
  //'penny' was found 2 times in the list.
  //  Enter a word for a partial search :
  //Words containing 'easy'
  //  easy
  //  uneasy
}

void WordInfo::MostCommonWords(int _count, bool _ignore_common_file) const
{
  std::vector<std::pair<std::string, int>> map_sorted_by_value;

  for (auto item = m_words_to_count.begin(); item != m_words_to_count.end(); ++item)
  {
    map_sorted_by_value.push_back(std::make_pair(item->first, item->second));
  }

  std::sort(map_sorted_by_value.begin(), map_sorted_by_value.end(),
    [](std::pair<std::string, int>& first, std::pair<std::string, int>& second)
    {
      return first.second > second.second;
    });

  if (_ignore_common_file)
  {
    std::cout << _count << "most frequent words (ignoring most commonly used):" << std::endl;
  }
  else
  {
    std::cout << _count << " most frequent words:" << std::endl;
    for (int i = 0; i < _count; ++i)
    {
      std::cout << "\t" << map_sorted_by_value[i].first << " " << map_sorted_by_value[i].second << std::endl;
    }
  }
}

void WordInfo::LongestWords(std::vector<std::string>& _words) const
{
}

void WordInfo::SetIgnoreWords(std::vector<std::string>& _ignore)
{
  for (const std::string& word : _ignore)
  {
    m_words_to_ignore[word] = word;
  }
}

int WordInfo::SearchForWord(const char* _word) const
{
  return 0;
}

unsigned WordInfo::GetTotalNumWords() const
{
  return m_total_words;
}

unsigned WordInfo::GetNumUniqueWords() const
{
  return m_words_to_count.size();
}

std::string WordInfo::GetLongestWord() const
{
  std::string longest_word;
  unsigned longest_word_count{0};
  for (auto item = m_words_to_count.begin(); item != m_words_to_count.end(); ++item) 
  {
    if (longest_word_count < item->first.size())
    {
      longest_word_count = item->first.size();
      longest_word = item->first;
    }
  }
  return longest_word;
}

unsigned WordInfo::GetAvgWordSize() const
{
  unsigned total_char_count{ 0 };
  for (auto item = m_words_to_count.begin(); item != m_words_to_count.end(); ++item)
  {
    total_char_count += item->first.size() * item->second;
  }
  return total_char_count / m_total_words;
}

WordInfo::~WordInfo()
{
}
