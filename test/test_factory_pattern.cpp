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
/*!\file    test_factory_pattern.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-26
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <iostream>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/factory.h"
#include "rrlib/util/patterns/singleton.h"

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------
using namespace rrlib::util;

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------


struct tShape
{
  tShape() {}
  virtual ~tShape() {}
};

struct tLine : public tShape
{
  tLine()
  {
    std::cout << "Creating tLine" << std::endl;
  }
};

struct tRectangle : public tShape
{
  tRectangle()
  {
    std::cout << "Creating tRectangle" << std::endl;
  }
};

struct tCircle : public tShape
{
  tCircle()
  {
    std::cout << "Creating tCircle" << std::endl;
  }
};

struct tEllipse : public tShape
{
  tEllipse()
  {
    std::cout << "Creating tEllipse" << std::endl;
  }
};


tLine *CloneLine(const tShape &)
{
  std::cout << "Cloning a line" << std::endl;
  return 0;
}
tRectangle *CloneRectangle(const tShape &)
{
  std::cout << "Cloning a rectangle" << std::endl;
  return 0;
}
tCircle *CloneCircle(const tShape &)
{
  std::cout << "Cloning a circle" << std::endl;
  return 0;
}

typedef tSingletonHolder<tFactory<tShape, std::string>> tShapeFactory;
typedef tSingletonHolder<tCloneFactory<tShape>> tShapeCloneFactory;

int main(int argc, char **argv)
{
  std::cout << "Testing factory" << std::endl;

  tShapeFactory::GetInstance().Register<tLine>("line");
  tShapeFactory::GetInstance().Register<tRectangle>("line");
  tShapeFactory::GetInstance().Register<tRectangle>("rectangle");
  tShapeFactory::GetInstance().Register<tCircle>("circle");
  tShapeFactory::GetInstance().Register<tEllipse>("ellipse");

  tShape *line = tShapeFactory::GetInstance().Create("line");
  tShape *rectangle = tShapeFactory::GetInstance().Create("rectangle");
  tShape *circle = tShapeFactory::GetInstance().Create("circle");
  tShape *ellipse = tShapeFactory::GetInstance().Create("ellipse");

  std::cout << "Testing clone factory" << std::endl;

  tShapeCloneFactory::GetInstance().Register(*line, &CloneLine);
  tShapeCloneFactory::GetInstance().Register(rectangle, &CloneRectangle);
  tShapeCloneFactory::GetInstance().Register(*circle, &CloneCircle);

  tShapeCloneFactory::GetInstance().Create(*line);
  tShapeCloneFactory::GetInstance().Create(*rectangle);
  tShapeCloneFactory::GetInstance().Create(*circle);
//  tShapeCloneFactory::GetInstance().Create(*ellipse);

  tShapeCloneFactory::GetInstance().Create(line);
  tShapeCloneFactory::GetInstance().Create(rectangle);
  tShapeCloneFactory::GetInstance().Create(circle);




//  tShape *foo = tShapeFactory::GetInstance().Create("foo");


  delete line;
  delete rectangle;
  delete circle;
  delete ellipse;

  return EXIT_SUCCESS;
}
