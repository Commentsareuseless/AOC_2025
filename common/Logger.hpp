/**
 * @file logger.hpp
 * @author Commentsareuseless
 * @brief Simple cli logging utility
 */

#pragma once

#include <fmt/core.h>
#include <fmt/color.h>

class lg
{
public:
  template <typename... T>
  static void printInf(fmt::format_string<T...> format, T&&... args) {
    if (verboseFlag) {
      vPrintMsg(LogLevel::INFO, format, fmt::make_format_args(args...));
    }
  }

  template <typename... T>
  static void printWrn(fmt::format_string<T...> format, T&&... args) {
    if (verboseFlag) {
      vPrintMsg(LogLevel::WARN, format, fmt::make_format_args(args...));
    }
  }

  template <typename... T>
  static void printErr(fmt::format_string<T...> format, T&&... args) {
    vPrintMsg(LogLevel::ERR, format, fmt::make_format_args(args...));
  }

  template <typename... T>
  static void printResultOk(fmt::format_string<T...> format, T&&... args) {
    vPrintMsg(LogLevel::RES_OK, format, fmt::make_format_args(args...));
  }

  static bool verboseFlag;

private:
  enum class LogLevel : uint32_t
  {
    INFO,
    WARN,
    ERR,
    RES_OK,
    RES_FAIL
  };

  static void vPrintMsg(LogLevel level,
                        fmt::string_view format,
                        fmt::format_args args);
};