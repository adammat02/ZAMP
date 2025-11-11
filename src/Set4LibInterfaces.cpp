#include "Set4LibInterfaces.hh"

void Set4LibInterfaces::AddLibInterface(const std::string &LibName)
{
  std::shared_ptr<LibraryInterface> pLibInterface = std::make_shared<LibraryInterface>();

  if (pLibInterface->init(LibName))
  {
    _LibInterfaces[pLibInterface->GetCmdName()] = pLibInterface;
    std::cout << "Dodanie interfejsu biblioteki: " << LibName << std::endl;
  }
  else
  {
    std::cerr << "!!! Nie mozna zainicjowac interfejsu biblioteki: " << LibName << std::endl;
  }
}

std::shared_ptr<LibraryInterface> Set4LibInterfaces::GetLibInterface(const std::string &LibName)
{
  auto it = _LibInterfaces.find(LibName);
  if (it != _LibInterfaces.end())
  {
    return it->second;
  }
  return nullptr;
}
