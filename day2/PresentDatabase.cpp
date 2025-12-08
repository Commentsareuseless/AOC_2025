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
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

inline constexpr std::initializer_list<const char* const> VERBOSE_FLAG_ALTS{
    common::KnownParams::VERBOSE_FLAG, common::KnownParams::VERBOSE_FLAG_SHORT};
inline constexpr std::initializer_list<const char* const> INPUT_FILES_ALTS{
    common::KnownParams::INPUT_FILE, common::KnownParams::INPUT_FILE_SHORT};

struct IdRange
{
  size_t from;
  size_t to;
};

IdRange parseRange(const std::string& rangeAsString) {
  constexpr char RANGE_SEPARATOR{'-'};

  const size_t separatorPos{rangeAsString.find(RANGE_SEPARATOR)};
  const std::string lowPart{rangeAsString.substr(0, separatorPos)};
  /* Make sure to exclude '-' below */
  const std::string highPart{rangeAsString.substr(separatorPos + 1)};

  return {std::stoull(lowPart), std::stoull(highPart)};
}

std::vector<uint8_t> toDigitVector(size_t numberToConvert) {
  constexpr size_t REASONABLE_MAX_NUMBER_OF_DIGITS{11};
  constexpr size_t CONVERSION_RADIX{10};
  std::vector<uint8_t> retval{};
  retval.reserve(REASONABLE_MAX_NUMBER_OF_DIGITS);

  for (size_t number{numberToConvert}; number > 0; number /= CONVERSION_RADIX) {
    retval.push_back(number % CONVERSION_RADIX);
  }

  return retval;
}

size_t sumWeirdPatterns(const IdRange& range) {
  size_t sumSoFar{0};

  for (size_t presentId{range.from}; presentId < range.to; ++presentId) {
    const auto digitVec{toDigitVector(presentId)};
    if (0 != (digitVec.size() % 2)) {
      // Number is odd, so there are no weird patterns
      continue;
    }

    const size_t halfOfDigitVec{digitVec.size() / 2};
    size_t vecIdx{0};
    for (; vecIdx < halfOfDigitVec; vecIdx++) {
      /* Weird pattern is when some set of digits repeats within a number */
      /* Example: 1010 -> weird, 1234 -> valid */
      if (digitVec.at(vecIdx) != digitVec.at(vecIdx + halfOfDigitVec)) {
        break;
      }
    }

    if (vecIdx == halfOfDigitVec) {
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