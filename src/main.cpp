#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibraryInterface.hh"
#include "ProgramInterpreter.hh"

using namespace std;

int main(int argc, char *args[])
{

  ProgramInterpreter ProgInterp;

  ProgInterp.Read_XML_Config("config/config.xml");
  ProgInterp.ExecProgram("../opis_dzialan.txt");
}
