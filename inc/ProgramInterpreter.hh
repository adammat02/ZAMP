#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include "Set4LibInterfaces.hh"
#include "Scene.hh"
#include "ComChannel.hh"

#define LINE_SIZE 500

class ProgramInterpreter
{
  Set4LibInterfaces _LibManager;
  Scene _Scn;
  ComChannel _Chann2Serv;

  bool ExecPreprocesor(const char *NazwaPliku, std::istringstream &Stream4Cmds);
  bool OpenConnection();

public:
  ~ProgramInterpreter();

  bool init();

  bool Read_XML_Config(const char *NazwaPliku);
  bool ExecProgram(const char *NazwaPliku);
};

#endif
