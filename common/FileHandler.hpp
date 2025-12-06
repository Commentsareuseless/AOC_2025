/**
 * @file FileHandler.hpp
 * @author Commentsareuseless
 * @brief File reading utility
 */
#pragma once

#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <cstdio>
#include <cstdint>
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
  bool GetLine(std::string& out_line) const noexcept;

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
   * @brief Open existing file for reading
   *
   * @param path path to file
   *
   * @return unique_ptr to opened file (may be nullptr if file doesn't exist)
   */
  static File Open(std::string_view path) noexcept;

  /**
   * @brief File iterator, allows iterating through
   *        lines in text files
   */
  struct line_iterator
  {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::string;
    using difference_type   = uint32_t;
    using pointer           = std::string*;
    using reference         = std::string&;

    enum class ContentPtrPos : difference_type
    {
      FILE_BEGIN = std::numeric_limits<difference_type>::min(),
      FILE_END   = std::numeric_limits<difference_type>::max(),
    };

    explicit line_iterator(ContentPtrPos startPos, File& file);

    std::string operator*();
    line_iterator& operator++();
    bool operator==(const line_iterator& other);
    bool operator!=(const line_iterator& other);

  private:
    std::reference_wrapper<File> fileRef;
    uint32_t fileContentPtr;
    std::string currentLine;
  };

  line_iterator begin() {
    return line_iterator{line_iterator::ContentPtrPos::FILE_BEGIN, *this};
  }
  line_iterator end() {
    return line_iterator{line_iterator::ContentPtrPos::FILE_END, *this};
  }
  // Const iterator not supported yet
  // const line_iterator cbegin() const {
  //   return line_iterator{line_iterator::ContentPtrPos::FILE_BEGIN, *this};
  // }
  // const line_iterator cend() const {
  //   return line_iterator{line_iterator::ContentPtrPos::FILE_END, *this};
  // }

private:
  static constexpr auto fileDeleter{[](FILE* filePtr) {
    // lg::printInf("Closing file: {}", filePtr);
    std::fclose(filePtr);
  }};

  std::unique_ptr<FILE, decltype(fileDeleter)> fileHdl;
};
} // namespace common