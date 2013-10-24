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
/*!\file    rrlib/util/tTransformTime.cpp
 *
 * \author  Bernd Helge Schaefer
 *
 * \date    2006-06-06
 *
 */
//----------------------------------------------------------------------

#include "rrlib/util/tTransformTime.h"


using namespace rrlib::util;

tTransformTime::tTransformTime(const tTime& transformante_time_base,
                               const tTime& transformer_time_base)
{
  this->ChangeTimeBase(transformante_time_base,
                       transformer_time_base);
}

void tTransformTime::ChangeTimeBase(const tTime& transformante_time_base,
                                    const tTime& transformer_time_base)
{
  this->last_transformante = transformante_time_base;
  this->last_transformer = transformer_time_base;
}

void tTransformTime::Transform(tTime& transformante, const tTime& transformer)
{
  /*  fprintf (stderr, "transformante: %ld, %ld\n",
    transformante.TvSec (),
    transformante.TvUSec ());
  fprintf (stderr, "transformer: %ld, %ld\n",
    transformer.TvSec (),
    transformer.TvUSec ());

  fprintf (stderr, "last_transformante: %ld, %ld\n",
    last_transformante.TvSec (),
    last_transformante.TvUSec ());
  fprintf (stderr, "last_transformer: %ld, %ld\n",
    last_transformer.TvSec (),
    last_transformer.TvUSec ());*/

  //temporarily store adapted transformante in last_transformer in order to minimise number object creations
  this->last_transformer += (transformante - this->last_transformante);

  //set last transformante to the current transformante
  this->last_transformante = transformante;

  //copy the transformed time to the transformante
  transformante = this->last_transformer;

  //update the last transformer with the current transformer
  this->last_transformer = transformer;

  /*  fprintf (stderr, "adapted transformante: %ld, %ld\n\n\n",
    transformante.TvSec (),
    transformante.TvUSec ());*/

}
