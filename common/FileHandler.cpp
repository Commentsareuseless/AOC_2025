#include "FileHandler.hpp"

#include "Logger.hpp"

#include <cstdio>
#include <memory>
#include <stdint.h>
#include <utility>

constexpr uint32_t ARBITRARY_NUM_OF_CHARS_READ_AT_ONCE{60};

FileHandler::FileHandler(FILE* hdl) : handle(hdl), endOfFile(false) {}

FileHandler::FileHandler(FileHandler&& other) noexcept :
    handle{other.handle}, endOfFile(other.endOfFile) {}

FileHandler::~FileHandler() {
  if (nullptr != handle) {
    const int retval = std::fclose(handle);

    if (0 > retval) {
      lg::printErr("Errors occured on file close");
    } else {
      lg::printInf("Closed input file");
    }
  }
}

FileHandler& FileHandler::operator=(FileHandler&& other) noexcept {
  handle    = other.handle;
  endOfFile = other.endOfFile;
  return *this;
}

bool FileHandler::GetNextLine(std::string& out_line) noexcept {
  bool retval{true};
  out_line.clear();
  out_line.resize(ARBITRARY_NUM_OF_CHARS_READ_AT_ONCE);

  for (char& input : out_line) {
    const int retChar = std::fgetc(handle);
    if (EOF == retChar) {
      // We've read whole file
      retval    = false;
      endOfFile = true;
      break;
    }

    const char chr = static_cast<char>(retChar);
    if ('\n' == chr) {
      // End of line, also return
      break;
    }

    // Otherwise save read char
    input = chr;
  }

  return retval;
}

FileHandler::File_ptr FileHandler::Open(std::string_view path) noexcept {

  FILE* hdl = nullptr;

  hdl = std::fopen(path.data(), "r");
  if (nullptr == hdl) {
    lg::printErr("Provided file does not exist or path is invalid");
    lg::printInf("Provided path:\n\t- {}", path);
    return File_ptr{nullptr};
  } else {
    lg::printInf("Opened {} file", path);
  }

  return File_ptr{new FileHandler(hdl)};
}
