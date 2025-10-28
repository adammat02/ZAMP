#ifndef LIBRARYINTERFACE_HH
#define LIBRSRYINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

class LibInterface
{

  void *pLibHnd;
  AbstractInterp4Command *(*pCreateCmd)(void);
  const char *(*pCmdName)(void);

public:
  LibInterface();
  ~LibInterface();

  bool init(const std::string &fileName);
  AbstractInterp4Command *GetCmd();
  std::string GetCmdName() const;
};

#endif
