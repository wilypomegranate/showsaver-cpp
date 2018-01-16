#include "dvb/atsc/types/EventInformationTable.hpp"
#include <cstdint>

namespace showsaver {
namespace dvb {
namespace atsc {
class EventInformationTableParser {
public:
  EventInformationTableParser() {}

  template <class T>
  std::size_t parse(T &callback_class, const unsigned char *buffer,
                    std::size_t size) {

    parse_buffer_.insert(parse_buffer_.end(), buffer, buffer + size);
    if (parse_buffer_.size() >= 3) {
      section_length_ =
          (std::uint16_t(parse_buffer_[1] << 8) | parse_buffer_[2]);
      section_length_ &= 0xFFF;
    }
    if (section_length_ > 0 && parse_buffer_.size() >= section_length_) {
      std::size_t size = table_.init(parse_buffer_, section_length_);
      clear_parsed_bytes(size);
    }
    return 0;
  }

private:
  std::vector<unsigned char> parse_buffer_;
  std::uint16_t section_length_;
  EventInformationTable table_;

  void clear_parsed_bytes(std::size_t bytes_parsed) {
    parse_buffer_.erase(parse_buffer_.begin(),
                        parse_buffer_.begin() + bytes_parsed);
  }
};
}
}
}
