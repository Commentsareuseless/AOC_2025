#include "Logger.hpp"

bool lg::verboseFlag{false};

void lg::vPrintMsg(LogLevel level,
                   fmt::string_view format,
                   fmt::format_args args) {
  switch (level) {
    case LogLevel::ERR: {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "[ERR]\t");
    } break;
    case LogLevel::WARN: {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "[WRN]\t");
    } break;
    case LogLevel::INFO: {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan), "[INF]\t");
    } break;
    case LogLevel::RES_OK: {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "[RESULT]\t");
    } break;
  }
  fmt::vprintln(stdout, format, args);
}