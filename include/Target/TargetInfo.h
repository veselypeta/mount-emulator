#pragma once
#include <string>
#include <string_view>

namespace me {

class Target {
public:
  enum VendorType {
    VT_Unknown = 0,
    //
    VT_Skywatcher,
  };

  enum ModelType {
    MT_Unknown,
    //
    MT_SW_EQ6,
  };

private:
  std::string Data;
  VendorType Vendor;
  ModelType Model;

public:
  Target() : Vendor(), Model() {}
  explicit Target(std::string_view Str);

  VendorType getVendor() const;
  ModelType getModel() const;

  std::string_view getVendorName() const;
  std::string_view getModelName() const;

  static std::string_view getVendorTypeName(VendorType Kind);
  static std::string_view getModelTypeName(ModelType Kind);
  static VendorType getVendorTypeFromName(std::string_view Str);
  static ModelType getModelTypeFromName(std::string_view Str);

  bool isEquatorial() const;
  bool isAltAz() const;
};

} // namespace me
