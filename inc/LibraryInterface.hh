#ifndef LIBRARYINTERFACE_HH
#define LIBRARYINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

class LibraryInterface
{

  void *_pLibHnd;
  AbstractInterp4Command *(*_pCreateCmd)(void);
  const char *(*_pCmdName)(void);

public:
  LibraryInterface();
  ~LibraryInterface();

  bool init(const std::string &fileName);
  AbstractInterp4Command *GetCmd() const;
  std::string GetCmdName() const;
};

#endif
