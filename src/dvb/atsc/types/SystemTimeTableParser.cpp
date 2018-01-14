#include "dvb/atsc/types/SystemTimeTableParser.hpp"
#include <iostream>

namespace showsaver {
namespace dvb {
namespace atsc {
SystemTimeTableParser::SystemTimeTableParser()
    : current_pos_(0), num_held_bytes_(0) {}

// template <class T>
// std::size_t
// SystemTimeTableParser::parse(T &callback_class,
//                              const std::vector<unsigned char> &buffer) {
//   std::size_t bytes_parsed = 0;

//   // Read first byte for table_id
//   if (between(current_pos_, 0, 1)) {
//     bytes_parsed += parse_table_id(buffer);
//     current_pos_ += bytes_parsed;
//   }

//   // Read two more bytes to get to section length info
//   else if (between(current_pos_, 1, 3)) {
//     // bytes_parsed += 2;
//   }
//   return bytes_parsed;
// }

std::size_t SystemTimeTableParser::parse_table_id(const unsigned char *buffer,
                                                  std::size_t size) {
  // validate buffer is at least 1 byte.
  std::size_t parsed_bytes = 0;
  if (size > 0) {
    std::uint16_t table_id = buffer[0];
    std::cout << table_id << std::endl;
    parsed_bytes += 1;
  }
  return parsed_bytes;
}

std::size_t
SystemTimeTableParser::parse_section_length(const unsigned char *buffer,
                                            std::size_t size) {
  std::size_t parsed_bytes = 0;
  if (size > 1) {
    std::uint16_t section_length = (std::uint16_t(buffer[0] << 8) | buffer[1]);
    section_length &= 0xFFF;
    std::cout << section_length << std::endl;
    // std::cout.write(reinterpret_cast<const char *>(buffer.data()+1), 1);
    parsed_bytes += 2;
  }
  return parsed_bytes;
}

std::size_t
SystemTimeTableParser::parse_table_id_extension(const unsigned char *buffer,
                                                std::size_t size) {
  std::size_t parsed_bytes = 0;
  if (size > 1) {
    std::uint16_t table_extension_id = buffer[0];
    std::cout << table_extension_id << std::endl;
    parsed_bytes += 2;
  }
  return parsed_bytes;
}
}
}
}
