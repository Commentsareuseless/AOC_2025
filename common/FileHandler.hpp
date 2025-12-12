/**
 * @file FileHandler.hpp
 * @author Commentsareuseless
 * @brief File reading utility
 */
#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <cstdio>
#include <Logger.hpp>

namespace common
{
class File
{
public:
  File()            = delete;
  File(const File&) = delete;
  File(File&& other) noexcept;
  ~File() = default;

  File& operator=(const File&) = delete;
  File& operator=(File&& other) noexcept;

  explicit File(std::string_view filePath);

  /**
   * @brief Get next line of opened file
   *
   * @param out_line  - read line is written here
   * @retval true     - More data is left to read
   * @retval false    - EOF
   */
  bool GetLine(std::string& out_line, char separator = '\n') const noexcept;

  /**
   * @brief Check if file has been properly opened
   *
   * @return true   - File is ready for other operations
   * @return false  - Error while opening file
   */
  bool Valid() const noexcept;

  /**
   * @brief Get size of current file
   *
   * @return Size of opened file in bytes
   */
  size_t Size() const noexcept;

  /**
   * @brief Get specified number of characters from file (/file chunk)
   *
   * @param chunkSize - Number of characters to read
   * @return Read characters
   */
  std::string GetChunk(size_t chunkSize) const noexcept;

  /**
   * @brief Open existing file for reading
   *
   * @param path path to file
   *
   * @return unique_ptr to opened file (may be nullptr if file doesn't exist)
   */
  static File Open(std::string_view path) noexcept;

private:
  static constexpr auto fileDeleter{[](FILE* filePtr) {
    lg::printInf("Closing file!");
    std::fclose(filePtr);
  }};

  std::unique_ptr<FILE, decltype(fileDeleter)> fileHdl;
};
} // namespace common