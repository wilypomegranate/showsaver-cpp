#include "dvb/atsc/types/SystemTimeTable.hpp"
#include <cstdint>
#include <functional>
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
    std::size_t clear_bytes = 0;

    // For now, there'll be an intermediate buffer.
    // TODO - Only use the intermediate buffer when needed.
    parse_buffer_.insert(parse_buffer_.end(), buffer, buffer + size);

    // Read until section length.
    // Then wait until the end and parse in one go.
    if (parse_buffer_.size() >= 3) {
      // Get section length, bits 12>=24.
      section_length_ =
          (std::uint16_t(parse_buffer_[1] << 8) | parse_buffer_[2]);
      section_length_ &= 0xFFF;
    }

    if (section_length_ > 0 && parse_buffer_.size() >= section_length_) {
      std::size_t size = table_.init(parse_buffer_, section_length_);
      clear_parsed_bytes(size);
    }

    /*
    // Read first byte for table_id
    if (between(current_pos_, 0, 1)) {
      bytes_parsed = parse_function(parse_table_id, clear_bytes);
    }

    if (!continue_parsing(bytes_parsed)) {
      clear_parsed_bytes(clear_bytes);
      return clear_bytes;
    }

    // Read two more bytes to get to section length info
    if (between(current_pos_, 1, 3)) {
      bytes_parsed = parse_function(parse_section_length, clear_bytes);
    }

    if (!continue_parsing(bytes_parsed)) {
      clear_parsed_bytes(clear_bytes);
      return clear_bytes;
    }

    if (between(current_pos_, 3, 5)) {
      bytes_parsed = parse_function(parse_table_id_extension, clear_bytes);
    }

    if (!continue_parsing(bytes_parsed)) {
      clear_parsed_bytes(clear_bytes);
      return clear_bytes;
    }

    if (between(current_pos_, 5, 6)) {
      bytes_parsed = parse_function(parse_version_number, clear_bytes);
    }

    if (!continue_parsing(bytes_parsed)) {
      clear_parsed_bytes(clear_bytes);
      return clear_bytes;
    }
    */

    return 0;
  }
  static std::size_t parse_table_id(const unsigned char *, std::size_t);
  static std::size_t parse_section_length(const unsigned char *, std::size_t);
  static std::size_t parse_table_id_extension(const unsigned char *,
                                              std::size_t);
  static std::size_t parse_version_number(const unsigned char *, std::size_t);

private:
  std::size_t current_pos_;
  std::vector<unsigned char> parse_buffer_;
  SystemTimeTable table_;
  std::uint16_t section_length_;
  // std::array<unsigned char, N> held_bytes_;
  // static bool between(std::size_t, std::size_t, std::size_t);

  std::size_t
  parse_function(std::function<std::size_t(const unsigned char *, std::size_t)>,
                 std::size_t &);

  void clear_parsed_bytes(std::size_t bytes_parsed) {
    parse_buffer_.erase(parse_buffer_.begin(),
                        parse_buffer_.begin() + bytes_parsed);
  }
  bool continue_parsing(std::size_t bytes_parsed) {
    if (parse_buffer_.size() > 0 && bytes_parsed > 0) {
      return true;
    }
    return false;
  }
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
