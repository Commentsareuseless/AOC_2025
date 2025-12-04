/**
 * @file VaultLock.cpp
 * @author Commentsareuseless
 * @brief First dat puzzle
 * @version 0.1
 * @date 2025-12-04
 */
#include "fmt/base.h"
#include <Logger.hpp>
#include <Clap.hpp>

int main(int argc, char* argv[]) {
  params::Clap argParser{argc, argv};

  if (argParser.WasParamProvided(params::VERBOSE_FLAG_SHORT) ||
      argParser.WasParamProvided(params::VERBOSE_FLAG)) {
    lg::verboseFlag = true;
  }

  lg::printInf("Dziala :)");
  lg::printErr("Verbose flag: {}", lg::verboseFlag);
  return 0;
}