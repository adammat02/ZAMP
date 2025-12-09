#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibraryInterface.hh"
#include "ProgramInterpreter.hh"

using namespace std;

int main(int argc, char *args[])
{
  if (argc != 3)
  {
    cerr << "Niepoprawna ilosc argumentow: [program][cmds][xml]" << endl;
    return -1;
  }
  const char *cmds = args[1];
  const char *xml = args[2];

  ProgramInterpreter ProgInterp;

  if(ProgInterp.init())
  {
    ProgInterp.Read_XML_Config(xml);
    ProgInterp.ExecProgram(cmds);
  }
  return 0;
}
