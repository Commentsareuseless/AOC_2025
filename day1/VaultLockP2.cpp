/**
 * @file VaultLock.cpp
 * @author Commentsareuseless
 * @brief First day puzzle
 * @version 0.1
 * @date 2025-12-04
 */
#include <Logger.hpp>
#include <Clap.hpp>
#include <FileHandler.hpp>
#include <cstdint>
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

class Dial
{
public:
  Dial() {}

  enum class TurnDirection : uint8_t
  {
    LEFT,
    RIGHT
  };

  struct DialTurnState
  {
    uint32_t dialPosition;
    uint32_t zeroCrosses;
  };

  DialTurnState Turn(uint32_t value, TurnDirection direction) {
    // Turning the dial with multiples of DIAL_MAX_VALUE doesn't really
    // change anything
    const uint32_t actualTurnValue{value % DIAL_MAX_VALUE};

    // Number of full rotations of a dial before moving it a meaningful
    // value which equals the number of times the dial crossed 0
    // before further computations
    const uint32_t numOfFullRotations{value / DIAL_MAX_VALUE};

    DialTurnState retval{};

    switch (direction) {
      case TurnDirection::LEFT: {
        lg::printInf("Turining LEFT by {}!", actualTurnValue);
        retval = turnLeft(actualTurnValue);
      } break;
      case TurnDirection::RIGHT: {
        lg::printInf("Turining RIGHT by {}!", actualTurnValue);
        retval = turnRight(actualTurnValue);
      } break;
    }

    retval.zeroCrosses += numOfFullRotations;
    currentPos = retval.dialPosition;
    return retval;
  }

private:
  constexpr DialTurnState turnLeft(uint32_t value) const {
    if (value > currentPos) {
      return {DIAL_MAX_VALUE - (value - currentPos),
              /* Dial ending at 0 is a special case, where we don't want
                 to increment "0 cross counter" (because we've stopped at 0) */
              (currentPos == 0) ? 0u : 1u};
    }
    return {currentPos - value, 0};
  }

  constexpr DialTurnState turnRight(uint32_t value) const {
    const uint32_t retval{currentPos + value};
    return {retval % DIAL_MAX_VALUE, ((retval > DIAL_MAX_VALUE) ? 1u : 0u)};
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
  uint32_t zeroCrossesTotal{0};
  for (const auto& line : common::FileIterator(inputFile)) {
    if (line.empty()) {
      lg::printInf("Found empty line!");
      continue;
    }
    const auto turnDir{(line.front() == 'L') ? Dial::TurnDirection::LEFT :
                                               Dial::TurnDirection::RIGHT};

    const uint32_t turnValue{std::stoul(line.substr(1))};
    const auto [dialPos, timesCrossed0]{vaultDial.Turn(turnValue, turnDir)};

    lg::printInf("Dial points at: {}", dialPos);
    lg::printInf("Zero crosses {}", timesCrossed0);

    zeroCrossesTotal += timesCrossed0;
    if (dialPos == 0) { ++dialAt0Cnt; }
    lg::printInf("Total zeros count: {}", dialAt0Cnt + zeroCrossesTotal);
  }

  lg::printInf("Zero crossed during rotation: {}", zeroCrossesTotal);
  lg::printInf("Stopped at 0: {}", dialAt0Cnt);

  lg::printResultOk("The password is: {}", dialAt0Cnt + zeroCrossesTotal);

  return 0;
}