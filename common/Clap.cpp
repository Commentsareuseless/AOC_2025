#include "Clap.hpp"

#include "argh.h"

#include <Logger.hpp>

static void configArguments(argh::parser& parser) {
  parser.add_param(params::VALID_CL_ARGS);
}

Clap::Clap() { configArguments(cmdInput); }

bool Clap::Parse(int argc, char* argv[]) {
  cmdInput.parse(argc, argv);
  // if (!cmdInput[params::VALID_CL_ARGS]) {
  //   lg::printErr("Provide valid params!");
  //   lg::printErr("None of received params are valid");
  //   return false;
  // }

  if (cmdInput[{params::VERBOSE_FLAG, params::VERBOSE_FLAG_SHORT}]) {
    lg::verboseFlag = true;
  }

  return true;
}

bool Clap::WasParamProvided(const std::string& paramName) {
  return static_cast<bool>(cmdInput(paramName));
}

std::string Clap::GetParamValue(const std::string& paramName) {
  if (!cmdInput(paramName)) { return std::string{}; }

  return cmdInput(paramName).str();
}
