/**
 * @file PresentDatabase.cpp
 * @author Commentsareuseless
 * @brief Second day puzzle
 * @version 0.1
 * @date 2025-12-07
 */


#include <Logger.hpp>
#include <Clap.hpp>
#include <FileIterator.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <span>

inline constexpr std::initializer_list<const char* const> VERBOSE_FLAG_ALTS{
    common::KnownParams::VERBOSE_FLAG, common::KnownParams::VERBOSE_FLAG_SHORT};
inline constexpr std::initializer_list<const char* const> INPUT_FILES_ALTS{
    common::KnownParams::INPUT_FILE, common::KnownParams::INPUT_FILE_SHORT};

inline constexpr size_t REASONABLE_MAX_NUMBER_OF_DIGITS{14};

struct IdRange
{
  size_t from;
  size_t to;
};

static constexpr std::array POSSIBLE_PATTERN_SIZES{
    1,
    2,
};

IdRange parseRange(const std::string& rangeAsString) {
  constexpr char RANGE_SEPARATOR{'-'};

  const size_t separatorPos{rangeAsString.find(RANGE_SEPARATOR)};
  const std::string lowPart{rangeAsString.substr(0, separatorPos)};
  /* Make sure to exclude '-' below */
  const std::string highPart{rangeAsString.substr(separatorPos + 1)};

  return {std::stoull(lowPart), std::stoull(highPart)};
}

std::span<uint8_t> toDigitVector(size_t numberToConvert) {
  constexpr size_t CONVERSION_RADIX{10};
  // Not really multi-thread friendly but who cares? :)
  static std::array<uint8_t, REASONABLE_MAX_NUMBER_OF_DIGITS> retval{};

  size_t numberLen{0};
  for (auto& elem : retval) {
    elem = numberToConvert % CONVERSION_RADIX;
    numberToConvert /= CONVERSION_RADIX;
    ++numberLen;

    if (numberToConvert == 0) { break; }
  }

  return {retval.data(), numberLen};
}

constexpr bool hasRepeatingPattern(const std::span<uint8_t>& numberToCheck,
                                   size_t patternSize) {
  /* First of all, make sure given pattern len "fits inside" given number */
  const size_t numberSize{numberToCheck.size()};
  /* Make sure not to cross the container boundary with pattern checking */
  const size_t numOfIterations{numberSize - patternSize};

  if (0 != (numberSize % patternSize)) { return false; }

  for (size_t idx{0}; idx < numOfIterations; ++idx) {
    if (numberToCheck[idx] != numberToCheck[idx + patternSize]) {
      /* we've found digit that does not match pattern */
      return false;
    }
  }
  /* We've iterated through whole number and didn't find any digit that
     *does not match the pattern */
  return true;
}

size_t sumWeirdPatterns(const IdRange& range) {
  size_t sumSoFar{0};

  for (size_t presentId{range.from}; presentId < range.to; ++presentId) {
    const auto digitVec{toDigitVector(presentId)};

    const size_t halfOfDigitVec{(digitVec.size() / 2) + 1};
    bool invalidIdFound{false};
    for (size_t patternSize{1}; patternSize < halfOfDigitVec; patternSize++) {
      /* Weird pattern is when some set of digits repeats within a number */
      /* Example: 1010 -> weird */
      /* 1234 -> valid */
      /* 999 -> weird */
      if (hasRepeatingPattern(digitVec, patternSize)) {
        invalidIdFound = true;
        break;
      }
    }

    if (invalidIdFound) {
      // We've iterated through half of the vector
      // and found weird pattern!
      sumSoFar += presentId;
      lg::printInf("Found weird pattern: {}", presentId);
    }
  }

  return sumSoFar;
}

int main(int argc, char* argv[]) {
  common::Clap argParser{argc, argv};

  if (argParser.IsFlagSet(VERBOSE_FLAG_ALTS)) { lg::verboseFlag = true; }

  const auto filePath{argParser.Value(INPUT_FILES_ALTS)};
  common::File inputFile{filePath};

  size_t sumOfWeirdIds{0};
  for (const std::string& line : common::FileIterator<','>{inputFile}) {
    if (line.empty()) {
      lg::printInf("Found empty line!");
      continue;
    }

    const IdRange presentIdRange{parseRange(line)};
    sumOfWeirdIds += sumWeirdPatterns(presentIdRange);
  }

  lg::printResultOk("The password is: {}", sumOfWeirdIds);

  return 0;
}