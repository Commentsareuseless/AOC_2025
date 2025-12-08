/**
 * @file PresentDatabase.cpp
 * @author Commentsareuseless
 * @brief Second day puzzle
 * @version 0.1
 * @date 2025-12-07
 */


#include <Logger.hpp>
#include <Clap.hpp>
#include <FileHandler.hpp>
#include <cstdint>
#include <string>
#include <FileIterator.hpp>

inline constexpr std::initializer_list<const char* const> VERBOSE_FLAG_ALTS{
    common::KnownParams::VERBOSE_FLAG, common::KnownParams::VERBOSE_FLAG_SHORT};
inline constexpr std::initializer_list<const char* const> INPUT_FILES_ALTS{
    common::KnownParams::INPUT_FILE, common::KnownParams::INPUT_FILE_SHORT};

/*********************************************/
/************* Puzzle input data *************/
inline constexpr uint32_t DIAL_STARTING_POSITION{50};
inline constexpr uint32_t DIAL_MAX_VALUE{100};
inline constexpr uint32_t DIAL_MIN_VALUE{0};
/*********************************************/


int main(int argc, char* argv[]) {
  common::Clap argParser{argc, argv};

  if (argParser.IsFlagSet(VERBOSE_FLAG_ALTS)) { lg::verboseFlag = true; }

  const auto filePath{argParser.Value(INPUT_FILES_ALTS)};
  lg::printInf("Got file path: {}", filePath);
  common::File inputFile{filePath};

  for (const auto& line : common::FileIterator<','>{inputFile}) {
    if (line.empty()) {
      lg::printInf("Found empty line!");
      continue;
    }
  }

  lg::printResultOk("The password is: {}");

  return 0;
}