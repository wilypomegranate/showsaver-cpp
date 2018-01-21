#include "dvb/atsc/types/MultipleStringStructure.hpp"

namespace showsaver {
namespace dvb {
namespace atsc {
MultipleStringStructure::MultipleStringStructure() {}

std::uint16_t
MultipleStringStructure::init(const std::vector<unsigned char>& buffer) {
  std::uint16_t parsed_bytes = 0;

  std::uint16_t number_strings = std::uint16_t(buffer[parsed_bytes]);
  parsed_bytes += 1;

  for (std::uint16_t i = 0; i < number_strings; i++) {
    std::uint32_t iso_639_language_code = 0;
    utils::parse_uint32_t(buffer.begin() + parsed_bytes, iso_639_language_code);
    iso_639_language_code &= 0xFFFFF00;
    iso_639_language_code = iso_639_language_code << 8;
    parsed_bytes += 3;

    std::uint8_t number_segments = 0;
    number_segments = buffer[parsed_bytes];
    parsed_bytes += 1;

    for (std::uint8_t i = 0; i < number_segments; i++) {
      std::uint8_t compression_type = buffer[parsed_bytes];
      parsed_bytes += 1;

      std::uint8_t mode = buffer[parsed_bytes];
      parsed_bytes += 1;

      std::uint16_t number_bytes = buffer[parsed_bytes];
      parsed_bytes += 1;

      if (number_bytes > 0) {
        std::string tmp(buffer.begin() + parsed_bytes,
                        buffer.begin() + parsed_bytes + number_bytes);
        text_.append(tmp);
      }
    }
  }

  return parsed_bytes;
}

} // namespace atsc
} // namespace dvb
} // namespace showsaver
