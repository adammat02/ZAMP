#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <vector>
#include "CuboidConfig.hh"

class Configuration {

  std::vector<std::string> _libraryPaths;
  std::vector<CuboidConfig> _cuboids;

  public:
    Configuration() {}

    void AddLibraryPath(const std::string &path) {
      _libraryPaths.push_back(path);
    }

    void AddCuboid(const CuboidConfig &cuboid) {
      _cuboids.push_back(cuboid);
    }

    const std::vector<std::string> &GetLibraryPaths() const {
      return _libraryPaths;
    }

    const std::vector<CuboidConfig> &GetCuboids() const {
      return _cuboids;
    }
};

#endif
