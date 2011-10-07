//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    sStringUtils.cpp
 *
 * \author  Bernd Helge Schaefer
 * \date    15.11.05
 *
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------

#include "rrlib/util/sStringUtils.h"

// boost includes
//#include <boost/algorithm/string.hpp> // trim

using namespace rrlib::util;

const size_t sStringUtils::max_chars;

void sStringUtils::Tokenize(const std::string& str,
                            std::vector<std::string>& tokens,
                            const std::string& delimiters)
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }
}

void sStringUtils::RemoveBracketsAndSpaces(const char* input_str, char* output_str, const char replace_token)
{

  unsigned int num_chars = std::min(strlen(input_str), max_chars);

  /*  if (num_chars > max_chars)
  {
    fprintf(stderr, "%s::RemoveBracketsAndSpaces>> string length (%d) exceeds max chars (%d)\n",
            Description(), num_chars, max_chars);
    fprintf(stderr, "Due to security reasons this is not permitted.\nOnly %d chars will be converted.\n",
            max_chars);
    num_chars = max_chars;
    }*/
  //@todo: line feeds, tabs etc are not handles so far ...
  for (unsigned int i = 0; i < num_chars; i++)
  {
    if (input_str [i] != '(' &&
        input_str [i] != ')' &&
        input_str [i] != '{' &&
        input_str [i] != '}' &&
        input_str [i] != '[' &&
        input_str [i] != ']' &&
        input_str [i] != ' ' &&
        input_str [i] != '.')
    {
      output_str [i] = input_str [i];
    }
    else
    {
      output_str [i] = replace_token;
    }
  }
  output_str [num_chars] = '\0';
}

void sStringUtils::Replace(std::string &input_str, const char* target_token, const char* replace_token)
{
  size_t pos = input_str.find(target_token);
  while (pos != std::string::npos)
  {
    input_str.replace(pos, strlen(target_token), replace_token);
    pos = input_str.find(target_token);
  }
}

void sStringUtils::Replace(char *input_str, char target_token, char replace_token)
{
  for (unsigned int i = 0; i < strlen(input_str); i++)
  {
    if (input_str[i] == target_token)
    {
      input_str[i] = replace_token;
    }
  }
}

void sStringUtils::TrimWhitespace(std::string &text)
{
  std::string check(text);
  std::string::size_type pos(text.size());

  //trim right side
  while (pos > 0 && std::isspace(text[pos - 1]))
    --pos;
  text.erase(pos);

  // trim left side
  pos = 0;
  while (pos < text.size() && std::isspace(text[pos]))
    ++pos;
  text.erase(0, pos);
  /*
  boost::trim(check);
  assert(text == check && "Internal Error: hand-coded string trimming does not return same value as boost::trim. Please go and tell tim.");
  */
}

void sStringUtils::RemoveMultipleWhitespaces(std::string &text)
{
  // search from left
  std::string::size_type counter = 0;
  while (counter < text.size() - 1)
  {
    if (std::isspace(text.at(counter)) && std::isspace(text.at(counter + 1)))
    {
      text.erase(counter, 1);
    }
    else
    {
      counter++;
    }
  }
}


bool sStringUtils::EndsWith(const std::string& text, const std::string& element)
{
  if (text.length() < element.length()) // if element is longer than text, the text can not contain the element
  {
    return false;
  }

  std::size_t element_pos = text.rfind(element);

  if (element_pos != std::string::npos)
  {
    return (element_pos == (text.length() - element.length())); // check whether the last characters equal the element
  }
  else
  {
    return false; // if element was not found in text
  }

}

bool sStringUtils::BeginsWith(const std::string& text, const std::string& element)
{
  return (text.find(element) == 0);
}

bool sStringUtils::StringToBool(std::string s)
{
  if ((s == "true") || (s == "1"))
    return true;
  else
    return false;
}

