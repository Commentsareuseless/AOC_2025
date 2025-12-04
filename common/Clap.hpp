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

namespace params
{
constexpr auto INPUT_FILE{"input"};
constexpr auto INPUT_FILE_SHORT{"i"};
constexpr auto VERBOSE_FLAG{"verbose"};
constexpr auto VERBOSE_FLAG_SHORT{"v"};

constexpr std::initializer_list<const char* const> VALID_CL_ARGS{
    INPUT_FILE, INPUT_FILE_SHORT, VERBOSE_FLAG, VERBOSE_FLAG_SHORT};
} // namespace params


class Clap
{
public:
  explicit Clap();

  bool Parse(int argc, char* argv[]);
  bool WasParamProvided(const std::string& paramName);
  std::string GetParamValue(const std::string& paramName);

private:
  argh::parser cmdInput;
};