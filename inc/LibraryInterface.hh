#ifndef LIBRARYINTERFACE_HH
#define LIBRARYINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

class LibInterface
{

  void *_pLibHnd;
  AbstractInterp4Command *(*_pCreateCmd)(void);
  const char *(*_pCmdName)(void);

public:
  LibInterface();
  ~LibInterface();

  bool init(const std::string &fileName);
  AbstractInterp4Command *GetCmd();
  std::string GetCmdName() const;
};

#endif
