#include "dvb/atsc/types/MasterGuideTable.hpp"

namespace showsaver {
namespace dvb {
namespace atsc {
MasterGuideTable::MasterGuideTable() {}
std::uint16_t MasterGuideTable::init(const std::vector<unsigned char> &buffer,
                                     const std::uint16_t size) {
  std::uint16_t parsed_bytes = 0;

  table_id_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  section_length_ = (buffer[parsed_bytes] << 8 | buffer[parsed_bytes + 1]);
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

  tables_defined_ = buffer[parsed_bytes] << 8;
  tables_defined_ |= buffer[parsed_bytes + 1];
  parsed_bytes += 2;
}
}
}
}
