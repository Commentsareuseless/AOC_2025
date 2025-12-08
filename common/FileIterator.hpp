/**
 * @file FileIterator.hpp
 * @author Commentsareuseless
 * @brief Utility to easily iterate through file contents
 * @version 0.1
 */
#pragma once

#include <FileHandler.hpp>
#include <cstdint>
#include <functional>
#include <type_traits>

namespace common
{
/* TODO: Make possible iterating over lines or
         any chunk of text or binary data separated
         by given separator or with given byte sizes.
         Make a "safety counter" that ensures the file
         will not be read over it's size in bytes */
template <char ContentSeparator = '\n'>
class FileIterator
{
public:
  explicit FileIterator(const File& ref) : fileRef(ref) {}

  class iterator
  {
  public:
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

    iterator(const File& file, ContentPtrPos startPos) :
        currentLine(),
        fileRef(file),
        fileContentPtr(static_cast<decltype(fileContentPtr)>(startPos)) {
      // Read first line
      if (startPos != ContentPtrPos::FILE_END) {
        currentLine.assign(readLine(file, fileContentPtr));
      }
    }

    std::string operator*() { return currentLine; }

    iterator& operator++() {
      currentLine.assign(readLine(fileRef.get(), fileContentPtr));
      return *this;
    }

    bool operator==(const iterator& other) {
      return fileContentPtr == other.fileContentPtr;
    }

    bool operator!=(const iterator& other) {
      return fileContentPtr != other.fileContentPtr;
    }

  private:
    std::string readLine(const File& fileRef, uint32_t& contentPtrRef) const {
      std::string retval{};
      const bool status{fileRef.GetLine(retval, ContentSeparator)};
      if (status) {
        contentPtrRef += retval.size();
      } else {
        /* End of file */
        contentPtrRef =
            static_cast<std::remove_reference_t<decltype(contentPtrRef)>>(
                ContentPtrPos::FILE_END);
      }

      return retval;
    }

    std::string currentLine;
    std::reference_wrapper<const File> fileRef;
    uint32_t fileContentPtr;
  };

  auto begin() -> iterator {
    return iterator{fileRef.get(), iterator::ContentPtrPos::FILE_BEGIN};
  }
  auto end() -> iterator {
    return iterator{fileRef.get(), iterator::ContentPtrPos::FILE_END};
  }
  auto cbegin() const -> const iterator {
    return iterator{fileRef.get(), iterator::ContentPtrPos::FILE_BEGIN};
  }
  auto cend() const -> const iterator {
    return iterator{fileRef.get(), iterator::ContentPtrPos::FILE_END};
  }

private:
  std::reference_wrapper<const File> fileRef;
};
} // namespace common