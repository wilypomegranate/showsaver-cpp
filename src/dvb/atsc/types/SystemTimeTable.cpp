#include "dvb/atsc/types/SystemTimeTable.hpp"
#include <cassert>
#include <iostream>

namespace showsaver {
namespace dvb {
namespace atsc {
SystemTimeTable::SystemTimeTable() {}
std::uint16_t SystemTimeTable::init(const std::vector<unsigned char> &buffer,
                                    const std::uint16_t section_length) {
  std::uint16_t parsed_bytes = 0;
  // TODO - Add buffer sizing validation
  table_id_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  section_length_ = (std::uint16_t(buffer[parsed_bytes] << 8) | buffer[parsed_bytes + 1]);
  section_length_ &= 0xFFF;
  parsed_bytes += 2;

  table_id_extension_ = buffer[parsed_bytes];
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

  system_time_ = 0;
  system_time_ = buffer[parsed_bytes] << 24;
  system_time_ |= buffer[parsed_bytes + 1] << 16;
  system_time_ |= buffer[parsed_bytes + 2] << 8;
  system_time_ |= buffer[parsed_bytes + 3];
  parsed_bytes += 4;

  std::cout << system_time_ << std::endl;

  gps_utc_offset_ = buffer[parsed_bytes];
  std::cout << std::uint16_t(gps_utc_offset_) << std::endl;
  parsed_bytes += 1;

  daylight_saving_ = buffer[parsed_bytes];
  parsed_bytes += 2;

  // There are a variable amount of descriptors.
  // At least during testing, I'm noticing that generally on STT messages, these
  // aren't set.
  // Annoyingly, this is calculated by subtracting
  // section_length from the size of the rest of data after section length.
  // This size is 17.

  // TODO - put these types of constants somewhere.
  std::uint16_t descriptor_length = section_length - STT_DESCRIPTOR_MIN_LENGTH;
  // There's nothing right now to do with descriptors of STT messages.
  parsed_bytes += descriptor_length;

  crc_ = buffer[parsed_bytes] << 24;
  crc_ |= buffer[parsed_bytes + 1] << 16;
  crc_ |= buffer[parsed_bytes + 2] << 8;
  crc_ |= buffer[parsed_bytes + 3];

  std::cout << dvb::utils::validate_crc_32(buffer.data(), parsed_bytes, crc_) << std::endl;
  parsed_bytes += 4;


  return parsed_bytes;
}
const std::uint16_t SystemTimeTable::table_id() const { return table_id_; }
}
}
}
