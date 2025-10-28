#include "LibraryInterface.hh"

#include <dlfcn.h>
#include <iostream>
#include <string>

LibInterface::LibInterface()
    : pLibHnd(nullptr), pCreateCmd(nullptr), pCmdName(nullptr) {}

LibInterface::~LibInterface()
{
  if (pLibHnd)
  {
    dlclose(pLibHnd);
    pLibHnd = nullptr;
  }
}

bool LibInterface::init(const std::string &fileName)
{
  pLibHnd = dlopen(fileName.c_str(), RTLD_LAZY);
  if (!pLibHnd)
  {
    std::cerr << "!!! Brak biblioteki: " << fileName << std::endl;
    return false;
  }

  void *pFun = dlsym(pLibHnd, "CreateCmd");
  if (!pFun)
  {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    return false;
  }
  pCreateCmd = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

  pFun = dlsym(pLibHnd, "GetCmdName");
  if (!pFun)
  {
    std::cerr << "!!! Nie znaleziono funkcji GetCmdName!" << std::endl;
    return false;
  }
  pCmdName = reinterpret_cast<const char *(*)(void)>(pFun);

  return true;
}

AbstractInterp4Command *LibInterface::GetCmd()
{
  return pCreateCmd();
}

std::string LibInterface::GetCmdName() const
{
  return std::string{pCmdName()};
}
