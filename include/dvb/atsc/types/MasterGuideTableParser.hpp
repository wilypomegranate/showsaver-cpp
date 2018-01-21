#include "dvb/atsc/types/MasterGuideTable.hpp"
#include <iostream>

namespace showsaver {
namespace dvb {
namespace atsc {
class MasterGuideTableParser {
public:
  MasterGuideTableParser() {}

  template <class T>
  std::size_t parse(T &callback_class, const unsigned char *buffer,
                    std::size_t size) {

    parse_buffer_.insert(parse_buffer_.end(), buffer, buffer + size);

    if (parse_buffer_.size() >= 3) {
      section_length_ =
          (std::uint16_t(parse_buffer_[1] << 8) | parse_buffer_[2]);
      section_length_ &= 0xFFF;
    }

    if (section_length_ > 0 && parse_buffer_.size() >= section_length_ + 3) {
      // Validate crc before doing anything here.
      // Otherwise acting on bad data could have undefined behavior.
      // The crc's are the last 4 bytes of the section.
      std::uint32_t crc = 0;
      utils::parse_uint32_t(parse_buffer_.begin() + ((section_length_+3) - 4),
                            crc);
      bool valid = utils::validate_crc_32(parse_buffer_.data(),
                                          ((section_length_+3) - 4),
                                          crc);
      std::size_t size = section_length_+3;
      if (valid) {
        table_.init(parse_buffer_, section_length_+3);
        callback_class(table_);
      }
      clear_parsed_bytes(size);
    }

    return 0;
  }

private:
  std::size_t current_pos_;
  std::vector<unsigned char> parse_buffer_;
  MasterGuideTable table_;
  std::uint16_t section_length_;

  void clear_parsed_bytes(std::size_t bytes_parsed) {
    parse_buffer_.erase(parse_buffer_.begin(),
                        parse_buffer_.begin() + bytes_parsed);
  }
};
}
}
}
