#include "FileHandler.hpp"

#include "Logger.hpp"
#include <cstddef>
#include <cstdio>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace common
{
namespace
{
inline constexpr uint32_t ARBITRARY_NUM_OF_CHARS_READ_AT_ONCE{20};
inline constexpr uint32_t MAX_LINE_WIDTH{100};

template <class Deleter>
std::string readFileUntill(const std::unique_ptr<FILE, Deleter>& filePtr,
                           const char stopChar) {

  std::string output{};
  output.reserve(ARBITRARY_NUM_OF_CHARS_READ_AT_ONCE);

  if (!filePtr) {
    lg::printErr("Provided file pointer is empty!");
    return {};
  }

  for (size_t byte{0}; byte < MAX_LINE_WIDTH; ++byte) {
    const int retChar{std::fgetc(filePtr.get())};
    /* Return if we've reached end of file */
    if (retChar == EOF) { return output; }

    const char newChar{static_cast<char>(retChar)};
    if (newChar == stopChar) {
      // Found end of current read chunk
      return output;
    }

    output += newChar;
  }

  lg::printWrn("Max line width reached");
  return output;
}
} // namespace


File::File(std::string_view filePath) :
    fileHdl(std::fopen(filePath.data(), "r"), fileDeleter) {
  if (!Valid()) {
    lg::printErr("Provided file path '{}' is invalid!", filePath);
  }
}

File::File(File&& other) noexcept : fileHdl{std::move(other.fileHdl)} {}

File& File::operator=(File&& other) noexcept {
  other.fileHdl.reset(other.fileHdl.release());
  return *this;
}

bool File::GetLine(std::string& out_line, char separator) const noexcept {
  const auto readStopCondition{
      [separator](char input) -> bool { return input == separator; }};

  out_line.clear();

  out_line.assign(readFileUntill(fileHdl, separator));

  return !out_line.empty();
}

bool File::Valid() const noexcept { return static_cast<bool>(fileHdl); }

size_t File::Size() const noexcept {
  /* Save current file ptr position to restore later */
  const auto seekPos{std::ftell(fileHdl.get())};

  if (0 != std::fseek(fileHdl.get(), 0, SEEK_END)) {
    /* Error */
    lg::printErr("{}:{}std::fseek() failed!", __FILE__, __LINE__);
    return 0;
  }

  /* In theory this result is unspecified in text mode
     but for UTF-8 encoding it should be the same as for binary
     mode (indicate number of bytes from the top of the file)
     so I'll use it anyway :) */
  const auto fileSize{std::ftell(fileHdl.get())};

  // Set file ptr to where we were before
  if (0 != std::fseek(fileHdl.get(), seekPos, SEEK_SET)) {
    /* Error*/
    lg::printErr("{}:{}std::fseek() failed!", __FILE__, __LINE__);
    return 0;
  }

  return (fileSize > 0) ? static_cast<size_t>(fileSize) : 0;
}

std::string File::GetChunk(size_t chunkSize) const noexcept {
  std::string output{};
  output.resize(chunkSize);
  (void)std::fread(output.data(), 1, chunkSize, fileHdl.get());
  return output;
}
} // namespace common