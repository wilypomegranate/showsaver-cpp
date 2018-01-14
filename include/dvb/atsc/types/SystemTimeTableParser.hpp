#include <cstdint>
#include <vector>

namespace showsaver {
namespace dvb {
namespace atsc {
class SystemTimeTableParser {
public:
  SystemTimeTableParser();
  template <class T>
  std::size_t parse(T &callback_class, const unsigned char *buffer,
                    std::size_t size) {
    std::size_t bytes_parsed = 0;

    const unsigned char* parse_buffer = buffer;

    // Read first byte for table_id
    if (between(current_pos_, 0, 1)) {
      bytes_parsed += parse_table_id(parse_buffer, size);
      current_pos_ += bytes_parsed;
    }

    parse_buffer += bytes_parsed;
    size -= bytes_parsed;

    // Read two more bytes to get to section length info
    if (between(current_pos_, 1, 3)) {
      bytes_parsed += parse_section_length(parse_buffer, size);
      current_pos_ += bytes_parsed;
    }

    parse_buffer += bytes_parsed;
    size -= bytes_parsed;

    if (between(current_pos_, 3, 5)) {
      bytes_parsed += parse_table_id_extension(parse_buffer, size);
      current_pos_ += bytes_parsed;
    }

    parse_buffer += bytes_parsed;
    size -= bytes_parsed;

    return bytes_parsed;
  }
  std::size_t parse_table_id(const unsigned char *, std::size_t);
  std::size_t parse_section_length(const unsigned char *, std::size_t);
  std::size_t parse_table_id_extension(const unsigned char*, std::size_t);

private:
  std::size_t current_pos_;
  std::size_t num_held_bytes_;
  // std::array<unsigned char, N> held_bytes_;
  // static bool between(std::size_t, std::size_t, std::size_t);
  static bool between(std::size_t pos, std::size_t start, std::size_t end) {
    if (pos >= start && pos < end) {
      return true;
    }
    return false;
  }
};
}
}
}
