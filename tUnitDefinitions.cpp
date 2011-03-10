#include "rrlib/util/tUnitDefinitions.h"

#include <cmath>

using namespace rrlib::util;

const tUnitInfo tUnitDefinitions::cDistanceUnitInfo [] =
{
  {"MM", 1.},
  {"CM", 10.},
  {"DM", 100.},
  {"M", 1000.}
};

const tUnitInfo tUnitDefinitions::cAngleUnitInfo [] =
{
  {"DEGREE", 100.},
  {"TENTH_DEGREE", 10.},
  {"HUNDREDTH_DEGREE", 1},
  {"THOUSANDTH_DEGREE", 0.1},
  {"RADIAN", (100.*180. / M_PI)}
};

std::shared_ptr<tUnitInfoUtils> tUnitDefinitions::distance_utils(
  new tUnitInfoUtils(tUnitDefinitions::cDistanceUnitInfo,
                     eDISTANCE_UNIT_DIMENSION,
                     "Distance Unit")
);

std::shared_ptr<tUnitInfoUtils> tUnitDefinitions::angle_utils(
  new tUnitInfoUtils(tUnitDefinitions::cAngleUnitInfo,
                     eANGLE_UNIT_DIMENSION,
                     "Angle Unit")
);

