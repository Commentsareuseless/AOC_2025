/**
 * @file FileHandler.hpp
 * @author Commentsareuseless
 * @brief File reading utility
 */
#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <stdio.h>

class FileHandler
{
public:
  using File_ptr = std::unique_ptr<FileHandler>;

  FileHandler()                   = delete;
  FileHandler(const FileHandler&) = delete;
  FileHandler(FileHandler&& other) noexcept;
  ~FileHandler();

  FileHandler& operator=(const FileHandler&) = delete;
  FileHandler& operator=(FileHandler&& other) noexcept;

  /**
   * @brief Get next line of opened file
   *
   * @param out_line  - read line is written here
   * @retval true     - More data is left to read
   * @retval false    - EOF
   */
  bool GetNextLine(std::string& out_line) noexcept;

  /**
   * @brief Open existing file for reading
   *
   * @param path path to file
   *
   * @return unique_ptr to opened file (may be nullptr if file doesn't exist)
   */
  static File_ptr Open(std::string_view path) noexcept;

private:
  FILE* handle;
  bool endOfFile;

  explicit FileHandler(FILE* hdl);
};
