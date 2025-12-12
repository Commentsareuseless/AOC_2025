/**
 * @file PresentDatabase.cpp
 * @author Commentsareuseless
 * @brief Second day puzzle
 * @version 0.1
 * @date 2025-12-07
 */
#include "fmt/base.h"
#include <Logger.hpp>
#include <Clap.hpp>
#include <FileIterator.hpp>
#include <array>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <string>

inline constexpr std::initializer_list<const char* const> VERBOSE_FLAG_ALTS{
    common::KnownParams::VERBOSE_FLAG, common::KnownParams::VERBOSE_FLAG_SHORT};
inline constexpr std::initializer_list<const char* const> INPUT_FILES_ALTS{
    common::KnownParams::INPUT_FILE, common::KnownParams::INPUT_FILE_SHORT};
inline constexpr size_t MAX_NUM_OF_TURNED_ON_BATTERIES{12};

template <size_t BankSize, typename Item_t = uint8_t>
class UsefulBatteryBank
{
public:
  void append(const uint8_t newValue) {
    const uint32_t shiftSquashPos{shouldBeShiftedLeft()};
    shiftLeft(shiftSquashPos);

    if (bank.back() < newValue) { bank.back() = newValue; }
  }

  size_t joltage() const {
    constexpr size_t RADIX{10};

    if constexpr (BankSize == 2) {
      return bank[0] * RADIX + bank[1];
    } else {
      size_t combinedJoltage{0};
      for (const auto battJoltage : bank) {
        combinedJoltage += battJoltage;
        combinedJoltage *= RADIX;
      }
      return combinedJoltage / RADIX;
    }
  }

private:
  /**
   * @brief Should the battery bank joltages be shifted
   *        to make room for more (larger)batteries.
   *
   * @return 0 if shift is not required, position of digit
   *         that will be "squashed" by shift if necessary
   * Example: bank: [8 1 8 1 8 1 9]
   * shouldBeShifted? -> Yes, because 8(idx: 2) > 1(idx: 1)
   * shiftPos -> 1 -> digits from idx:6 to idx: 1 should be shifted left
   * Shifting result -> [8 8 1 8 1 9 0]
   * Shifting bank left will make a room for another digit, that will make
   * a final number larger.
   * 8818190 > 8181819
   */
  uint32_t shouldBeShiftedLeft() const {
    for (size_t idx{0}; idx < (BankSize - 1); ++idx) {
      if (bank.at(idx) < bank.at(idx + 1)) {
        /* Higher "radix" digit is lower than lower "radix" */
        /* so shifting this number left will produce higher number */
        /* e.g.: 59 -> *leftShift* -> 90 */
        return idx;
      }
    }

    return BankSize;
  }

  /* Could have used operator overload but I don't like them */
  /**
   * @brief Shift whole bank vector by one position
   *
   * @param squashPos - Position that will be "squashed" during shift
   * Example: bank: [1 2 3 5 6] -> *shift, squashPos: 1* -> [1 3 5 6 0]
   */
  void shiftLeft(uint32_t squashPos) {
    Item_t prevValue{0};
    for (size_t idx{BankSize}; idx > squashPos; --idx) {
      Item_t& currentVal{bank.at(idx - 1)};
      Item_t tmp{currentVal};

      currentVal = prevValue;
      prevValue  = tmp;
    }
  }

  std::array<Item_t, BankSize> bank{};
};

constexpr uint8_t charToDigit(char input) {
  constexpr uint8_t FIRST_DIGIT_IN_ASCII{static_cast<uint8_t>('0')};
  const bool isDigit{static_cast<bool>(std::isdigit(input))};
  if (!isDigit) { return 0; }

  const uint8_t digit{static_cast<uint8_t>(input)};
  return digit - FIRST_DIGIT_IN_ASCII;
}

size_t sumJoltageInBank(const std::string& inputBank) {
  UsefulBatteryBank<MAX_NUM_OF_TURNED_ON_BATTERIES> usefulBank{};
  for (const char bat : inputBank) { usefulBank.append(charToDigit(bat)); }

  lg::printInf("Combined Joltage: {}", usefulBank.joltage());
  return usefulBank.joltage();
}

int main(int argc, char* argv[]) {
  common::Clap argParser{argc, argv};

  if (argParser.IsFlagSet(VERBOSE_FLAG_ALTS)) { lg::verboseFlag = true; }

  const auto filePath{argParser.Value(INPUT_FILES_ALTS)};
  common::File inputFile{filePath};

  size_t sumOfJoltages{0};
  for (const std::string& line : common::FileIterator<>{inputFile}) {
    if (line.empty()) {
      lg::printInf("Found empty line!");
      continue;
    }

    sumOfJoltages += sumJoltageInBank(line);
  }

  lg::printResultOk("The password is: {}", sumOfJoltages);

  return 0;
}