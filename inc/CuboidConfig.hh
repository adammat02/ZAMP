#ifndef CUBOIDCONFIG_HH
#define CUBOIDCONFIG_HH

#include <string>
#include "Vector3D.hh"

struct CuboidConfig
{
  std::string Name;
  Vector3D Shift;
  Vector3D Scale = {1.0, 1.0, 1.0};
  Vector3D RotXYZ_deg;
  Vector3D Trans_m;
  Vector3D RGB = {128.0, 128.0, 128.0};
};

#endif