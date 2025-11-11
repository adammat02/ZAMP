#include "LibraryInterface.hh"

#include <dlfcn.h>
#include <iostream>
#include <string>

LibraryInterface::LibraryInterface()
    : _pLibHnd(nullptr), _pCreateCmd(nullptr), _pCmdName(nullptr) {}

LibraryInterface::~LibraryInterface()
{
  if (_pLibHnd)
  {
    dlclose(_pLibHnd);
    _pLibHnd = nullptr;
  }
}

bool LibraryInterface::init(const std::string &fileName)
{
  _pLibHnd = dlopen(fileName.c_str(), RTLD_LAZY);
  if (!_pLibHnd)
  {
    std::cerr << "!!! Brak biblioteki: " << fileName << std::endl;
    return false;
  }

  void *pFun = dlsym(_pLibHnd, "CreateCmd");
  if (!pFun)
  {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    return false;
  }
  _pCreateCmd = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

  pFun = dlsym(_pLibHnd, "GetCmdName");
  if (!pFun)
  {
    std::cerr << "!!! Nie znaleziono funkcji GetCmdName!" << std::endl;
    return false;
  }
  _pCmdName = reinterpret_cast<const char *(*)(void)>(pFun);

  return true;
}

AbstractInterp4Command *LibraryInterface::GetCmd()
{
  return _pCreateCmd();
}

std::string LibraryInterface::GetCmdName() const
{
  return std::string{_pCmdName()};
}
