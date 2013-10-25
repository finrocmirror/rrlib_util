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
/*!\file    rrlib/util/sStringUtils.h
 *
 * \author  Bernd Helge Schaefer
 * \author  Jens Wettach
 *
 * \date    2005-11-15
 *
 * \brief   Contains static class sStringUtils
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#ifndef _rrlib_util_sStringUtils_h_
#define _rrlib_util_sStringUtils_h_

//C++ stl includes
#include <vector>
#include <cassert>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <iterator>


//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{
/*!
    Stream manipulator definition for reading a string from actual position within the stream up to the end of line.
*/
struct imanip
{
  std::istream& (*f)(std::istream&, std::string&);
  std::string& str;

  imanip(std::istream & (*ff)(std::istream&, std::string&), std::string& sstr) : f(ff), str(sstr)
  {}
}
;

/*!
    Overloading of stream operator >> to be used with new stream manipulator \em imanip.
*/
template <class Ch, class Tr>
std::basic_istream<Ch, Tr>& operator>>(std::basic_istream<Ch, Tr>& is, imanip m)
{
  return m.f(is, m.str);
};


/*!
    Stream manipulator implementation for reading a string from actual position within the stream up to the end of line.
*/
inline std::istream& get_line(std::istream& fin, std::string& str)
{
  std::ostringstream ss;
  char c;
  fin.get(c);
  while ((c == ' ' || c == '\t') && (c != '\n'))                                   // skip leading whitespace(s)
  {
    fin.get(c);
  }
  while (c != '\n' && !fin.eof())
  {
    //DEBUGMSG(DD_DEFAULT,DL_DEFAULT, "reading %c\n", c );
    ss << c;
    fin.get(c);
  }
  //    fin.ignore(0, '\n');   // skip end of line
  str = ss.str();
  if (fin.eof())
  {
    //DEBUGMSG(DD_DEFAULT,DL_DEFAULT, "---------------------------------------------------------------------------------->end of stream\n" );
  }
  return fin;
}




class sStringUtils
{

private:

  static bool StringCompare(const std::string &left, const std::string &right)
  {
    for (std::string::const_iterator lit = left.begin(), rit = right.begin(); lit != left.end() && rit != right.end(); ++lit, ++rit)
      if (std::tolower(*lit) < std::tolower(*rit))
        return true;
      else if (std::tolower(*lit) > std::tolower(*rit))
        return false;
    if (left.size() < right.size())
      return true;
    return false;
  }


public:

  static const char* Description()
  {
    return "sStringUtils";
  }

  static const size_t max_chars = 255;

  /*!
   * \brief Converts the input string to an upper case string.
   *
   * Note that if input and output string pointer are not the same, the
   * caller needs to assure that for the output string at least as
   * much bytes are allocated as the length of the input string.
   * Otherwise a memory violation will occur.
   *
   * \param input_str The string to be converted to upper case.
   * \param output_str Handle to the upper case string (May be the same as the input string for destructive mode of operation).
   */
  static void ToUpper(const char* input_str, char* output_str)
  {
    unsigned int num_chars = strlen(input_str);

    if (num_chars > max_chars)
    {
      fprintf(stderr, "%s::ToUpper>> string length (%d) exceeds max chars (%zu)\n",
              Description(), num_chars, max_chars);
      fprintf(stderr, "Due to security reasons this is not permitted.\nOnly %zu chars will be converted to upper case.\n",
              max_chars);
      num_chars = max_chars;
    }

    for (unsigned int i = 0; i < num_chars; i++)
    {
      output_str [i] = toupper(input_str [i]);
    }
    output_str [num_chars] = '\0';
  }

  /*!
   * \brief Converts the input string to an lower case string.
   *
   * For details see documentation of routine ToUpper().
   */
  static void ToLower(const char* input_str, char* output_str)
  {
    unsigned int num_chars = (strlen(input_str) < strlen(output_str) ? strlen(input_str) : strlen(output_str));

    if (num_chars > max_chars)
    {
      fprintf(stderr, "%s::ToLower>> string length (%d) exceeds max chars (%zu)\n",
              Description(), num_chars, max_chars);
      fprintf(stderr, "Due to security reasons this is not permitted.\nOnly %zu chars will be converted to lower case.\n",
              max_chars);
      num_chars = max_chars;
    }

    for (unsigned int i = 0; i < num_chars; i++)
    {
      output_str [i] = tolower(input_str [i]);
    }
    output_str [num_chars] = '\0';
  }

  /*!
   * \brief Removes brackets and spaces
   */
  static void RemoveBracketsAndSpaces(const char* input_str, char* output_str, const char replace_token = '_');

  /*!
   * \brief Splits a string into a list of tokes using the provided delimiter.
   *
   * \param str The string to be split up
   * \param tokens The list of tokens
   * \param The delimiter
   */
  static void Tokenize(const std::string& str,
                       std::vector<std::string>& tokens,
                       const std::string& delimiters);


  /*!
       * \brief Replaces a section of the current string by some other content.
       *
       * \param str The string whose content should be replaced
       * \param target_token The part of the string that should  be replaced
       * \param replace_token The token that should be placed in the string instead of the target_token
       */
  static void Replace(std::string &input_str, const char* target_token, const char* replace_token);

  /*!
       * \brief Replaces one character of the current string by an other char.
       *
       * \param str The string whose content should be replaced
       * \param target_token The character of the string that should  be replaced
       * \param replace_token The character that should be placed in the string instead of the target_token
       */

  static void Replace(char *input_str, char target_token, char replace_token);

  static std::string ConstReplace(const std::string &input_str, const char* target_token, const char* replace_token);

  /*!
   * Stream manipulator implementation for reading a string from actual position within the stream up to the end of line.
   * Uses function <get_line>, but provides normal stream manipulator interface.
   *
   * Example: input_stream >> sStringUtils::getline( word );
   *
   */
  static imanip getline(std::string& str)
  {
    return imanip(get_line, str);
  }


  /*!
   * \brief Replaces commata by points in the provided c string.
   *
   * \param str The c string in which all commata shall be replaced by points.
   */
  static void ReplaceCommasByPoints(char* str)
  {
    char comma [2];
    memset(comma, 0, 2);
    comma [0] = ',';
    //    fprintf (stderr, "test str: %s\n", test);
    char* temp_str = str;
    for (unsigned int i = 0; i < strlen(str); i++)
    {
      if (strncmp(comma, temp_str, 1) == 0)
      {
        temp_str [0] = '.';
        // fprintf (stderr, "replacing: %s\n", str);
      }
      temp_str++;
    }
  }


  /*!
   * \brief Trims whitespace at the front and the back of given string.
   * To be used as function object in for_each statements.
   *
   */
  template<class T>
  struct Trim : public std::unary_function<T, void>
  {
    void operator()(T& x)
    {
      TrimWhitespace(x);
    }
  };

  /*!
   * \brief Trims whitespace at the front and the back of given string
   *
   */
  static void TrimWhitespace(std::string &text);

  /*!
   * \brief Removes multiple whitespaces in the given string
   *
   */
  static void RemoveMultipleWhitespaces(std::string &text);

  /*!
     * \brief returns true if given element is first part of given text
     */
  static bool BeginsWith(const std::string& text, const std::string& element);

  /*!
     * \brief returns true if given element is last part of given text
     */
  static bool EndsWith(const std::string& text, const std::string& element);

  /*!
   * \brief Builds a list of strings from a list of character arrays.
   */
  static void BuildStringListFromCharArrays(std::vector <std::string>& name_list, const char* const* names, size_t number_of_names)
  {
    assert(names != NULL);
    name_list.clear();
    for (size_t i = 0; i < number_of_names; i++)
    {
      assert(names [i] != NULL);
      name_list.push_back(names [i]);
    }
  }

  static void BuildStringListFromCharArrays(std::vector <std::string>& name_list, const std::vector <const char*>& names)
  {
    name_list.clear();
    for (size_t i = 0; i < names.size(); i++)
    {
      assert(names [i] != NULL);
      name_list.push_back(names [i]);
    }
  }

  /*!
   * \brief Returns true if string equals "true" or "1".
   * \param s string to be checked
   */
  static bool StringToBool(std::string s);


  /*!
   * \brief Converting object to std::string and returning the string
   * \param object to be converted
   */
  template <class T>
  static std::string StringOf(const T& object)
  {
    std::ostringstream os;
    os << object;
    return (os.str());
  }

  /*!
   * \brief Converting object to std::string
   * \param object to be converted, string is stored in s
   */
  template <class T>
  static void StringOf(const T& object, std::string & s)
  {
    std::ostringstream os;
    os << object;
    s = os.str();
  }
  /*!
   * \brief Converting a std::string representing a hexadecimal number into a decimal number
   * \param string representing hexadecimal number
   */

  template<class T>
  static T HexStringToDecNumber(std::string str)
  {
    std::istringstream iss(str);
    T result = 0;
    iss >> std::hex >> result;
    return result;
  }


  /*!
   * \brief Enclosing string with the given prefix and suffix
   * \param input string, prefix, and suffix
   * \return the enclosed string
   */
  static std::string EncloseString(const char* string, const char* prefix, const char* suffix)
  {
    return std::string(std::string(prefix) + std::string(string) + std::string(suffix));
  }

  /*!
     * \brief Enclosing string with the given prefix and suffix
     * \param output string, where the enclosed string will be stored, input string, prefix, and suffix
     */
  static bool EncloseString(std::string &output_string, const char* input_string, const char* prefix, const char* suffix)
  {
    output_string = std::string(prefix) + std::string(input_string) + std::string(suffix);
    return true;
  }


  static bool SortStringVector(std::vector<std::string> &vec)
  {
    std::sort(vec.begin(), vec.end(), StringCompare);
    return true;
  }

  static int FindStringInArray(const char* str, char*const* str_array, size_t num_str_in_array)
  {
    char*const* descr_begin(&str_array[0]);
    char*const* descr_end(&str_array[0] + num_str_in_array);
    char*const* pos = std::find(descr_begin, descr_end, str);
    if (pos != descr_end)
      return std::distance(descr_begin, pos);
    else
      return -1;
  }

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}; // namespace util
}; // namespace rrlib
#endif

