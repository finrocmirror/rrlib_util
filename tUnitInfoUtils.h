//
// You received this file as part of MCA2
// Modular Controller Architecture Version 2
//
//Copyright (C) AG Robotersysteme TU Kaiserslautern
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-
//----------------------------------------------------------------------
/*!\file    tUnitInfoUtils.h
 *
 * \author  Bernd Helge Schaefer
 * \date    14.01.2008
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_tUnitInfoUtils_h_
#define _rrlib_util_tUnitInfoUtils_h_

#include "rrlib/util/sStringUtils.h"

#include <vector>
#include <string>
#include <assert.h>

namespace rrlib
{
namespace util
{

class tUnitInfo
{
public:
  const char* name;
  double reference_ratio;
};

class tUnitInfoUtils
{
public:
  tUnitInfoUtils(const tUnitInfo* unit_info, unsigned int unit_dimension, const char* description):
      unit_info(NULL),
      unit_dimension(0),
      description(NULL)
  {
    assert(unit_info != NULL);
    assert(description != NULL);
    assert(unit_dimension > 0);
    this->Init(unit_info,
               unit_dimension,
               description);
  }

  ~tUnitInfoUtils()
  {
    if (this->description != NULL)
    {
      free(this->description);
      this->description = NULL;
    }
  }

  const char* Description() const
  {
    if (this->description == NULL)
    {
      return "tUnitInfoUtils";
    }
    else
    {
      return this->description;
    }
  }

  void Init(const tUnitInfo* unit_info, unsigned int unit_dimension, const char* description)
  {
    if (this->description != NULL)
    {
      free(this->description);
      this->description = NULL;
    }
    this->description = strndup(description, rrlib::util::sStringUtils::max_chars);
    this->unit_dimension = unit_dimension;
    this->unit_info = unit_info;

    this->unit_info_names.clear();
    for (unsigned int i = 0; i < this->unit_dimension; ++i)
    {
      this->unit_info_names.push_back(this->unit_info[i].name);
    }
  }

  void PrintUnitList() const
  {
    if (this->unit_info == NULL)
    {
      fprintf(stderr, "%s::PrintUnitList>> No units were defined in this class.\n", this->Description());
      return;
    }

    fprintf(stdout, "%s:\n", this->Description());
    for (unsigned int i = 0; i < unit_dimension; i++)
    {
      fprintf(stdout, "\t%s (%d) -> reference: %f\n",
              this->unit_info [i].name, i, this->unit_info [i].reference_ratio);
    }
    fprintf(stdout, "\n");
  }

  double ConversionFactor(unsigned int input_unit, unsigned int output_unit) const
  {
    if (input_unit == output_unit)
    {
      return 1.0;
    }
    else
    {
      return (this->unit_info [input_unit].reference_ratio / this->unit_info [output_unit].reference_ratio);
    }
  }

  bool StringToUnit(const char* unit_str, unsigned int& unit) const
  {
    char inner_unit_str [rrlib::util::sStringUtils::max_chars + 1];
    strncpy(inner_unit_str, unit_str, rrlib::util::sStringUtils::max_chars);
    rrlib::util::sStringUtils::ToUpper(inner_unit_str, inner_unit_str);

    char comp_unit_str [rrlib::util::sStringUtils::max_chars + 1];

    for (unsigned int i = 0; i < unit_dimension; i++)
    {
      rrlib::util::sStringUtils::ToUpper(this->unit_info [i].name, comp_unit_str);

      if (strcmp(comp_unit_str, inner_unit_str) == 0)
      {
        unit = i;
        return true;
      }
    }
    fprintf(stderr, "StringToUnit>> Illegal distance unit string '%s'\n\n",
            unit_str);
    this->PrintUnitList();
    unit = unit_dimension;
    return false;
  }

  const char* ToString(unsigned int unit_id) const
  {
    if (this->unit_dimension > unit_id)
    {
      return this->unit_info [unit_id].name;
    }
    else
    {
      fprintf(stderr, "%s::ToString>> Illegal Unit ID: %d!\n",
              this->Description(), unit_id);
      return NULL;
    }
  }

  const std::vector<std::string>& GetUnitInfoNames()
  {
    assert(this->unit_info != NULL);
    assert(!this->unit_info_names.empty());
    assert(this->unit_dimension > 0);
    return this->unit_info_names;
  }

private:
  /*!
   * \brief
   */
  const tUnitInfo* unit_info;
  unsigned int unit_dimension;
  char* description;

  std::vector<std::string> unit_info_names;
};
}
}
#endif
