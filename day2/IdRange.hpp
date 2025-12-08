/**
 * @file IdRange.hpp
 * @author Commentsareuseless
 * @brief Utility class to hold range of present IDs
 * @date 2025-12-08
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <iterator>

struct IdRange
{
  size_t from;
  size_t to;

  class iterator
  {
  public:
    /* It could be random access iterator but I don't have time for that :) */
    using iterator_category = std::forward_iterator_tag;
    using value_type        = size_t;
    using difference_type   = size_t;
    using pointer           = value_type*;
    using reference         = value_type&;

    explicit iterator(size_t startPos) : current(startPos) {}

    size_t operator*() { return current; }

    iterator& operator++() {
      ++current;
      return *this;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const {
      return current != other.current;
    }

  private:
    size_t current;
  };

  auto begin() const -> iterator { return iterator{from}; }
  auto end() const -> iterator { return iterator{to + 1}; }
  auto cbegin() const -> const iterator { return iterator{from}; }
  auto cend() const -> const iterator { return iterator{to + 1}; }
};
