#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <list>
#include "CuboidConfig.hh"

class Configuration {

  std::list<std::string> _libraryPaths;
  std::list<CuboidConfig> _cuboids;

  public:
    Configuration() {}

    void AddLibraryPath(const std::string &path) {
      _libraryPaths.push_back(path);
    }

    void AddCuboid(const CuboidConfig &cuboid) {
      _cuboids.push_back(cuboid);
    }

    const std::list<std::string> &GetLibraryPaths() const {
      return _libraryPaths;
    }

    const std::list<CuboidConfig> &GetCuboids() const {
      return _cuboids;
    }
};

#endif
