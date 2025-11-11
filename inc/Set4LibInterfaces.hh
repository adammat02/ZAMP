#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibraryInterface.hh"
#include <map>
#include <memory>
#include <string>

class Set4LibInterfaces
{
  std::map<std::string, std::shared_ptr<LibraryInterface>> _LibInterfaces;

public:
  void AddLibInterface(const std::string &LibName);
  std::shared_ptr<LibraryInterface> GetLibInterface(const std::string &LibName);
};

#endif