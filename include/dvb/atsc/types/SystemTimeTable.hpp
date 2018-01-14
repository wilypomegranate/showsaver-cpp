#include <bitset>
#include <cstdint>

namespace showsaver {
namespace dvb {
namespace atsc {
class SystemTimeTable {
public:
  SystemTimeTable();
  const std::uint8_t get_table_id() const;
  void set_table_id(const std::uint8_t table_id);

private:
  std::uint8_t table_id;
  std::bitset<1> section_syntax_indicator_;
  std::bitset<1> private_indicator_;
  std::bitset<2> reserved_;
  std::bitset<12> section_length;
  std::bitset<16> table_id_extension_;
  std::bitset<2> reserved2_;
  std::bitset<5> version_number_;
  std::bitset<1> current_next_indicator_;
  std::uint8_t section_number_;
  std::uint8_t last_section_number_;
  std::uint8_t protocol_version_;
  std::uint32_t system_time_;
  std::uint8_t gps_utc_offset_;
  std::uint16_t daylight_saving_;
  std::uint32_t crc_;
};
}
}
}
