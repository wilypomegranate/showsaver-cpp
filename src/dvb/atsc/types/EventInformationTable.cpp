#include "dvb/atsc/types/EventInformationTable.hpp"

namespace showsaver {
namespace dvb {
namespace atsc {
EventInformationSection::EventInformationSection() {}

EventInformationTable::EventInformationTable() {}

  std::uint16_t EventInformationSection::init(const std::vector<unsigned char>&buffer) {
  std::uint16_t parsed_bytes = 0;

  reserved_ = buffer[parsed_bytes] >> 6;
  utils::parse_uint16_t(buffer.begin()+parsed_bytes, event_id_);
  event_id_ &= 0x3FFF;

  utils::parse_uint32_t(buffer.begin()+parsed_bytes, start_time_);
  parsed_bytes += 4;

  reserved2_ = buffer[parsed_bytes] >> 6;
  etm_location_ = buffer[parsed_bytes] >> 6;

  utils::parse_uint32_t(buffer.begin()+parsed_bytes, length_in_seconds_);
  length_in_seconds_ &= 0xFFFFF00;
  length_in_seconds_ = length_in_seconds_ << 8;
  parsed_bytes += 3;

  title_length_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  title_text_ = std::string(parsed_bytes, title_length_);
  parsed_bytes += title_length_;

  reserved3_ = buffer[parsed_bytes] << 4;
  utils::parse_uint16_t(buffer.begin()+parsed_bytes, descriptors_length_);
  descriptors_length_ &= 0xFFF;
  parsed_bytes += 2;

  parsed_bytes += descriptors_length_;

  return parsed_bytes;
}

  std::uint16_t EventInformationTable::init(const std::vector<unsigned char> &buffer,
                   std::uint16_t size) {
  std::uint16_t parsed_bytes = 0;

  parsed_bytes += dvb::utils::parse_header(buffer, table_id_, section_length_);

  utils::parse_uint16_t(buffer.begin()+parsed_bytes, source_id_);
  parsed_bytes += 2;

  reserved2_ = buffer[parsed_bytes] >> 6;
  version_number_ = (buffer[parsed_bytes] >> 1) & 0x1f;
  current_next_indicator_ = buffer[parsed_bytes] & 0x1;
  parsed_bytes += 1;

  section_number_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  last_section_number_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  protocol_version_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  num_events_in_section_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  for (std::uint16_t i = 0; i < (std::uint16_t)(num_events_in_section_); i++) {
    std::vector<unsigned char> table_buffer(buffer.begin() + parsed_bytes,
                                            buffer.end());
    parsed_bytes += add_event_section(table_buffer);
  }

  utils::parse_uint32_t(buffer.begin()+parsed_bytes, crc_);
  parsed_bytes += 4;

  // std::cout << dvb::utils::validate_crc_32(buffer.data(), parsed_bytes, crc_) << std::endl;

  return parsed_bytes;
}

std::uint16_t EventInformationTable::add_event_section(const std::vector<unsigned char>& buffer) {
  EventInformationSection section;
  std::uint16_t parsed_bytes = section.init(buffer);
  sections_.push_back(section);
  }
}
}
}
