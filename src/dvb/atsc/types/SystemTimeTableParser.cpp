#include "dvb/atsc/types/SimpleTimeTableParser.hpp"

template <class T, std::size_t N>
SystemTimeTableParser::SystemTimeTableParser(T callback_class)
    : callback_class_(callback_class), current_pos_(0), num_held_bytes_(0),
      held_bytes_() {}

template <class T, std::size_t N>
std::size_t
SystemTimeTableParser::parse(const std::array<unsigned char, N> &buffer) {
  std::size_t bytes_parsed = 0;

  // Read first byte for table_id
  if (current_pos_ > 0 && current_pos_ <= 1) {
    parse_table_id(buffer);
    bytes_parsed += 1;
    current_pos_ += 1;
  }

  // Read two more bytes to get to section length info
  if (current_pos_ > 1 && current_pos_ <= 3) {
    bytes_parsed += 2;
  }
}

template <class T, std::size_t N>
void SystemTimeTableParser::parse_table_id(
    const std::array<unsigned char, N> &buffer) {}
