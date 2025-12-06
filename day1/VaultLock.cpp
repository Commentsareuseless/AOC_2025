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
#include <cstdint>
#include <string>

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

class Dial
{
public:
  Dial() {}

  enum class TurnDirection : uint8_t
  {
    LEFT,
    RIGHT
  };

  uint32_t Turn(uint32_t value, TurnDirection direction) {
    // Turning the dial with multiples of DIAL_MAX_VALUE doesn't really
    // change anything
    const uint32_t actualTurnValue{value % DIAL_MAX_VALUE};

    switch (direction) {
      case TurnDirection::LEFT: {
        lg::printInf("Turining LEFT by {}!", actualTurnValue);
        currentPos = turnLeft(actualTurnValue);
      } break;
      case TurnDirection::RIGHT: {
        lg::printInf("Turining RIGHT by {}!", actualTurnValue);
        currentPos = turnRight(actualTurnValue);
      } break;
    }

    return currentPos;
  }

private:
  constexpr uint32_t turnLeft(uint32_t value) const {
    if (value > currentPos) { return DIAL_MAX_VALUE - (value - currentPos); }
    return currentPos - value;
  }

  constexpr uint32_t turnRight(uint32_t value) const {
    const uint32_t retval{currentPos + value};
    return retval % DIAL_MAX_VALUE;
  }

  uint32_t currentPos{DIAL_STARTING_POSITION};
};

int main(int argc, char* argv[]) {
  common::Clap argParser{argc, argv};

  if (argParser.IsFlagSet(VERBOSE_FLAG_ALTS)) { lg::verboseFlag = true; }

  const auto filePath{argParser.Value(INPUT_FILES_ALTS)};
  lg::printInf("Got file path: {}", filePath);
  common::File inputFile{filePath};

  Dial vaultDial{};
  uint32_t dialAt0Cnt{0};
  for (const auto& line : inputFile) {
    if (line.empty()) {
      lg::printInf("Found empty line!");
      continue;
    }
    const auto turnDir{(line.front() == 'L') ? Dial::TurnDirection::LEFT :
                                               Dial::TurnDirection::RIGHT};

    const uint32_t turnValue{std::stoul(line.substr(1))};
    const auto dialPos{vaultDial.Turn(turnValue, turnDir)};

    lg::printInf("Dial points at: {}", dialPos);

    if (dialPos == 0) { ++dialAt0Cnt; }
  }

  lg::printResultOk("The password is: {}", dialAt0Cnt);

  return 0;
}