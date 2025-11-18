#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibraryInterface.hh"
#include "ProgramInterpreter.hh"

using namespace std;

int main(int argc, char *args[])
{

  ProgramInterpreter ProgInterp;

  // ProgInterp.AddLibrary("libInterp4Move.so");
  // ProgInterp.AddLibrary("libInterp4Set.so");
  // ProgInterp.AddLibrary("libInterp4Pause.so");
  // ProgInterp.AddLibrary("libInterp4Rotate.so");

  // ProgInterp.ExecProgram("../opis_dzialan.txt");

  Configuration Config;
  ProgInterp.Read_XML_Config("config/config.xml", Config);
  std::cout << "Wczytane sciezki do bibliotek:" << std::endl;
  for (const auto &path : Config.GetLibraryPaths())
  {
    std::cout << "  " << path << std::endl;
  }

  std::cout << "Wczytane cuboidy:" << std::endl;
  for (const auto &cuboid : Config.GetCuboids())
  {
    std::cout << "  Name: " << cuboid.Name << std::endl;
    std::cout << "    Shift: " << cuboid.Shift << std::endl;
    std::cout << "    Scale: " << cuboid.Scale << std::endl;
    std::cout << "    RotXYZ_deg: " << cuboid.RotXYZ_deg << std::endl;
    std::cout << "    Trans_m: " << cuboid.Trans_m << std::endl;
    std::cout << "    RGB: " << cuboid.RGB << std::endl;
  }
}
