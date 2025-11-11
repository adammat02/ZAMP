#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibraryInterface.hh"
#include "ProgramInterpreter.hh"

using namespace std;

int main()
{

  ProgramInterpreter ProgInterp;

  ProgInterp.AddLibrary("libInterp4Move.so");
  ProgInterp.AddLibrary("libInterp4Set.so");
  ProgInterp.AddLibrary("libInterp4Pause.so");
  ProgInterp.AddLibrary("libInterp4Rotate.so");

  ProgInterp.ExecProgram("../opis_dzialan.txt");
}
