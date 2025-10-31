#pragma once
#include <string>

namespace me {

class Driver {
  std::string MountModel;

public:
  void SetMountModel(const std::string &Model) { MountModel = Model; }
};

} // namespace me
