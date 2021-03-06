//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/util/sStringUtils.cpp
 *
 * \author  Bernd Helge Schaefer
 *
 * \date    2005-11-15
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------

#include "rrlib/util/sStringUtils.h"
#include "rrlib/util/string.h"

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

const size_t sStringUtils::max_chars;

void sStringUtils::Tokenize(const std::string& str,
                            std::vector<std::string>& tokens,
                            const std::string& delimiters)
{
  return util::Tokenize(str, tokens, delimiters);
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

std::string sStringUtils::ConstReplace(const std::string &input_str, const char* target_token, const char* replace_token)
{
  std::string output_str = input_str;
  size_t pos = output_str.find(target_token);
  while (pos != std::string::npos)
  {
    output_str.replace(pos, strlen(target_token), replace_token);
    pos = output_str.find(target_token);
  }
  return output_str;
}

void sStringUtils::TrimWhitespace(std::string &text)
{
  return util::TrimWhitespace(text);
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
  return util::EndsWith(text, element);
}

bool sStringUtils::BeginsWith(const std::string& text, const std::string& element)
{
  return util::StartsWith(text, element);
}

bool sStringUtils::StringToBool(std::string s)
{
  if ((s == "true") || (s == "1"))
    return true;
  else
    return false;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
