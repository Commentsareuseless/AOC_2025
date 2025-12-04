#include "Clap.hpp"

#include "argh.h"

#include <Logger.hpp>

namespace params
{
static void configArguments(argh::parser& parser) {
  parser.add_param(params::VALID_CL_ARGS);
}

Clap::Clap() { configArguments(cmdInput); }

Clap::Clap(int argc, char** argv) {
  configArguments(cmdInput);
  Parse(argc, argv);
}

void Clap::Parse(int argc, char* argv[]) { cmdInput.parse(argc, argv); }

bool Clap::WasParamProvided(const std::string& paramName) {
  return static_cast<bool>(cmdInput[paramName]);
}

std::string Clap::GetParamValue(const std::string& paramName) {
  if (!cmdInput(paramName)) { return std::string{}; }

  return cmdInput(paramName).str();
}

} // namespace params