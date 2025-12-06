/**
 * @file VaultLock.cpp
 * @author Commentsareuseless
 * @brief First dat puzzle
 * @version 0.1
 * @date 2025-12-04
 */
#include <Logger.hpp>
#include <Clap.hpp>
#include <FileHandler.hpp>
#include <string>

inline constexpr std::initializer_list<const char* const> VERBOSE_FLAG_ALTS{
    common::KnownParams::VERBOSE_FLAG, common::KnownParams::VERBOSE_FLAG_SHORT};
inline constexpr std::initializer_list<const char* const> INPUT_FILES_ALTS{
    common::KnownParams::INPUT_FILE, common::KnownParams::INPUT_FILE_SHORT};

int main(int argc, char* argv[]) {
  common::Clap argParser{argc, argv};

  if (argParser.IsFlagSet(VERBOSE_FLAG_ALTS)) { lg::verboseFlag = true; }

  const auto filePath{argParser.Value(INPUT_FILES_ALTS)};
  common::File inputFile{filePath};
  lg::printInf("Got file path: {}", filePath);

  std::string line{};
  const bool opSucc{inputFile.GetLine(line)};
  lg::printInf("Got line: {}", line);

  return 0;
}