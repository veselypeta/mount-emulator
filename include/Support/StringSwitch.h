#pragma once
#include <optional>
#include <string_view>

namespace me {

template <class T, typename R = T> class StringSwitch {
  const std::string_view Str;
  std::optional<T> Result;

public:
  explicit StringSwitch(std::string_view S) : Str(S), Result() {}

  StringSwitch(const StringSwitch &) = delete;
  void operator=(const StringSwitch &) = delete;
  void operator=(StringSwitch &&Other) = delete;
  StringSwitch(StringSwitch &&Other)
      : Str(Other.Str), Result(std::move(Other.Result)) {}
  ~StringSwitch() = default;

  StringSwitch &Case(std::string_view S, T Value) {
    if (!Result && Str == S) {
      Result = std::move(Value);
    }
    return *this;
  }

  [[nodiscard]] R Default(T Value) {
    if (Result)
      return std::move(*Result);
    return Value;
  }

  [[nodiscard]] operator R() {
    assert(Result && "Fell of the end of string-switch");
    return std::move(*Result);
  }
};
} // namespace me
