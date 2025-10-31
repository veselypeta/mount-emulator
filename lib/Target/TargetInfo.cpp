#include <Support/StringSwitch.h>
#include <Target/TargetInfo.h>
#include <algorithm>
#include <cassert>

using namespace me;

Target::Target(std::string_view Str)
    : Data{Str.begin(), Str.end()}, Vendor(VT_Unknown), Model(MT_Unknown) {
  auto SplitPoint = std::find(Data.begin(), Data.end(), '-');
  const std::string_view VendorName{Data.begin(), SplitPoint};
  Vendor = getVendorTypeFromName(VendorName);
  if (SplitPoint == Data.end()) {
    return;
  }
  std::advance(SplitPoint, 1);
  const std::string_view ModelName{SplitPoint, Data.end()};

  Model = getModelTypeFromName(ModelName);
}

std::string_view Target::getVendorTypeName(VendorType Kind) {
  switch (Kind) {
  case VT_Unknown:
    return "unknown";
  case VT_Skywatcher:
    return "skywatcher";
  }
  __builtin_unreachable();
}

std::string_view Target::getModelTypeName(ModelType Kind) {
  switch (Kind) {
  case MT_Unknown:
    return "unknown";
  case MT_SW_EQ6:
    return "eq6";
  }
  __builtin_unreachable();
}

Target::VendorType Target::getVendorTypeFromName(std::string_view Str) {
  return me::StringSwitch<VendorType>(Str)
      .Case("skywatcher", VT_Skywatcher)
      .Default(VT_Unknown);
}

Target::ModelType Target::getModelTypeFromName(std::string_view Str) {
  return me::StringSwitch<ModelType>(Str)
      .Case("eq6", MT_SW_EQ6)
      .Default(MT_Unknown);
}

Target::ModelType Target::getModel() const { return Model; }
Target::VendorType Target::getVendor() const { return Vendor; }

std::string_view Target::getVendorName() const {
  return Target::getVendorTypeName(Vendor);
}

std::string_view Target::getModelName() const {
  return Target::getModelTypeName(Model);
}

bool Target::isEquatorial() const {
  switch (getModel()) {
  case Target::MT_SW_EQ6:
    return true;
  default:
    break;
  }
  return false;
}

bool Target::isAltAz() const { return false; }
