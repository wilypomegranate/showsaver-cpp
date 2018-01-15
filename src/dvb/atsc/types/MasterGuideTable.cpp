#include "dvb/atsc/types/MasterGuideTable.hpp"
#include <iostream>

namespace showsaver {
namespace dvb {
namespace atsc {
MasterGuideTable::MasterGuideTable() {}
std::uint16_t MasterGuideTable::init(const std::vector<unsigned char> &buffer,
                                     const std::uint16_t size) {
  std::uint16_t parsed_bytes = 0;

  table_id_ = buffer[parsed_bytes];
  parsed_bytes += 1;

  section_length_ =
      (std::uint16_t(buffer[parsed_bytes] << 8) | buffer[parsed_bytes + 1]);
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

  tables_defined_ = buffer[parsed_bytes] << 8;
  tables_defined_ |= buffer[parsed_bytes + 1];
  parsed_bytes += 2;

  // Tables are variable length fields. Number of fields stored in
  // tables_defined_.

  // The PsipTable init function should be called table_defined_ times.
  // TODO - This should probably use iterators instead of a copy.

  for (std::uint16_t i = 0; i < tables_defined_; i++) {
    std::vector<unsigned char> table_buffer(buffer.begin() + parsed_bytes,
                                            buffer.end());
    parsed_bytes += add_psip_table(table_buffer);
  }

  reserved3_ = buffer[parsed_bytes] >> 7;

  descriptors_length_ = buffer[parsed_bytes] << 8;
  descriptors_length_ |= buffer[parsed_bytes + 1];
  descriptors_length_ &= 0xFFF;
  parsed_bytes += 2;

  crc_ = buffer[parsed_bytes] << 24;
  crc_ |= buffer[parsed_bytes + 1] << 16;
  crc_ |= buffer[parsed_bytes + 2] << 8;
  crc_ |= buffer[parsed_bytes + 3];

  // std::cout << dvb::utils::validate_crc_32(buffer.data(), parsed_bytes, crc_) << std::endl;
  parsed_bytes += 4;

  return parsed_bytes;
}

std::uint16_t
MasterGuideTable::add_psip_table(const std::vector<unsigned char> &buffer) {
  PsipTable table;
  std::uint16_t parsed_bytes = table.init(buffer);
  tables_.push_back(table);
  return parsed_bytes;
}

PsipTable::PsipTable() {}

std::uint16_t PsipTable::init(const std::vector<unsigned char> &buffer) {
  std::uint16_t parsed_bytes = 0;
  table_type_ = buffer[parsed_bytes] << 8;
  table_type_ |= buffer[parsed_bytes + 1];
  parsed_bytes += 2;

  reserved_ = buffer[parsed_bytes] << 5;

  table_type_pid_ = buffer[parsed_bytes] << 8;
  table_type_pid_ |= buffer[parsed_bytes + 1];
  table_type_pid_ &= 0x1fff;

  parsed_bytes += 2;

  reserved2_ = buffer[parsed_bytes] << 5;
  table_type_version_number_ = (buffer[parsed_bytes] >> 1) & 0x1f;
  parsed_bytes += 1;

  num_bytes_ = 0;
  num_bytes_ = buffer[parsed_bytes] << 24;
  num_bytes_ |= buffer[parsed_bytes + 1] << 16;
  num_bytes_ |= buffer[parsed_bytes + 2] << 8;
  num_bytes_ |= buffer[parsed_bytes + 3];
  parsed_bytes += 4;

  reserved3_ = buffer[parsed_bytes] << 6;

  table_type_descriptors_length_ = buffer[parsed_bytes] << 8;
  table_type_descriptors_length_ |= buffer[parsed_bytes + 1];
  table_type_descriptors_length_ &= 0xFFF;
  parsed_bytes += 2;

  // Skip descriptors for now.
  // TODO - Evaluate whether parsed_bytes should actually return uint32_t.
  // Since table bytes are provided in uint32_t, we could overflow parsed_bytes.
  parsed_bytes += table_type_descriptors_length_;
  return parsed_bytes;
}
}
}
}
