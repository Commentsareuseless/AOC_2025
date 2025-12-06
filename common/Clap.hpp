/**
 * @file Clap.hpp
 * @author Commentsareuseless
 * @brief Command line arguments parser
 *        Wrapper for argh to limit code repetitions
 */
#pragma once

#include <argh.h>

#include <initializer_list>
#include <string>

namespace common
{
struct KnownParams
{
  static constexpr auto INPUT_FILE{"input"};
  static constexpr auto INPUT_FILE_SHORT{"i"};
  static constexpr auto VERBOSE_FLAG{"verbose"};
  static constexpr auto VERBOSE_FLAG_SHORT{"v"};

  static constexpr std::initializer_list<const char* const> VALID_CL_ARGS{
      INPUT_FILE, INPUT_FILE_SHORT, VERBOSE_FLAG, VERBOSE_FLAG_SHORT};
};

class Clap
{
public:
  using AltParamList_t = std::initializer_list<const char* const>;

  explicit Clap();
  Clap(int argc, char** argv);

  void Parse(int argc, char** argv);
  bool IsFlagSet(const std::string& paramName);
  bool IsFlagSet(const AltParamList_t& altParamList);
  std::string Value(const std::string& paramName);
  std::string Value(const AltParamList_t& altParamList);

private:
  argh::parser cmdInput;
};
} // namespace common