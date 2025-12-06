/**
 * @file Clap.cpp
 * @author Commentsareuseless
 * @brief Command line arguments parser
 *        Wrapper for argh to limit code repetitions
 */
#include "Clap.hpp"

#include "argh.h"

#include <Logger.hpp>

namespace common
{
static void configArguments(argh::parser& parser) {
  parser.add_param(KnownParams::VALID_CL_ARGS);
}

Clap::Clap() { configArguments(cmdInput); }

Clap::Clap(int argc, char** argv) {
  configArguments(cmdInput);
  Parse(argc, argv);
}

void Clap::Parse(int argc, char* argv[]) { cmdInput.parse(argc, argv); }

bool Clap::IsFlagSet(const std::string& paramName) {
  return cmdInput[paramName];
}

bool Clap::IsFlagSet(const AltParamList_t& altParamList) {
  return cmdInput[altParamList];
}

std::string Clap::Value(const std::string& paramName) {
  return cmdInput(paramName).str();
}

std::string Clap::Value(const AltParamList_t& altParamList) {
  return cmdInput(altParamList).str();
}

} // namespace common