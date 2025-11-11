#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include "Set4LibInterfaces.hh"

#define LINE_SIZE 500

class ProgramInterpreter
{
  Set4LibInterfaces _LibManager;

  bool ExecPreprocesor(const char *NazwaPliku, std::istringstream &Stream4Cmds);

public:
  void AddLibrary(const std::string &LibName);
  bool ExecProgram(const char *NazwaPliku);
};

#endif
