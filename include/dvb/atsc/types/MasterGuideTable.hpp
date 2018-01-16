#include "dvb/utils/ParserUtils.hpp"
#include <bitset>
#include <cstdint>
#include <vector>

namespace showsaver {
namespace dvb {
namespace atsc {
class PsipTable {
public:
  PsipTable();
  std::uint16_t init(const std::vector<unsigned char> &);

private:
  std::uint16_t table_type_;
  std::bitset<3> reserved_;
  std::uint16_t table_type_pid_;
  std::bitset<3> reserved2_;
  std::bitset<5> table_type_version_number_;
  std::uint32_t num_bytes_;
  std::bitset<4> reserved3_;
  std::uint16_t table_type_descriptors_length_;
};
class MasterGuideTable {
public:
  MasterGuideTable();
  std::uint16_t init(const std::vector<unsigned char> &, const std::uint16_t);
  std::uint16_t add_psip_table(const std::vector<unsigned char>&);
  std::uint32_t crc() const {
    return crc_;
  }

private:
  std::uint8_t table_id_;
  std::bitset<1> section_syntax_indicator_;
  std::bitset<1> private_indicator_;
  std::bitset<2> reserved_;
  std::bitset<12> section_length_;
  std::uint16_t table_id_extension_;
  std::bitset<2> reserved2_;
  std::bitset<5> version_number_;
  std::bitset<1> current_next_indicator_;
  std::uint8_t section_number_;
  std::uint8_t last_section_number_;
  std::uint8_t protocol_version_;
  std::uint16_t tables_defined_;
  std::vector<PsipTable> tables_;
  std::bitset<4> reserved3_;
  std::uint16_t descriptors_length_;
  std::uint32_t crc_;
};
}
}
}
