#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibraryInterface.hh"

using namespace std;

int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move)
  {
    cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Move, "CreateCmd");
  if (!pFun)
  {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;

  dlclose(pLibHnd_Move);

  LibInterface libSet;
  libSet.init("libInterp4Set.so");

  pCmd = libSet.GetCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;

  LibInterface libRot;
  libRot.init("libInterp4Rotate.so");

  pCmd = libRot.GetCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;

  LibInterface libP;
  libP.init("libInterp4Pause.so");

  pCmd = libP.GetCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;


  delete pCmd;
}
