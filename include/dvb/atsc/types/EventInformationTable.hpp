#include "dvb/utils/ParserUtils.hpp"
#include <bitset>
#include <cstdint>
#include <string>
#include <vector>

namespace showsaver {
namespace dvb {
namespace atsc {
class EventInformationSection {
public:
  EventInformationSection();
  std::uint16_t init(const std::vector<unsigned char>&);
  std::uint32_t start_time() const {
    return start_time_;
  }
  std::string title_text() const {
    return title_text_;
  }

private:
  std::bitset<2> reserved_;
  std::uint16_t event_id_;
  std::uint32_t start_time_;
  std::bitset<2> reserved2_;
  std::bitset<2> etm_location_;
  std::uint32_t length_in_seconds_;
  std::uint8_t title_length_;
  std::string title_text_;
  std::bitset<4> reserved3_;
  std::uint16_t descriptors_length_;
};

class EventInformationTable {
public:
  EventInformationTable();
  std::uint16_t init(const std::vector<unsigned char>&, std::uint16_t);
  std::uint16_t add_event_section(const std::vector<unsigned char>&);
  std::vector<EventInformationSection> sections() const {
    return sections_;
  }

private:
  std::uint8_t table_id_;
  std::bitset<1> section_syntax_indicator;
  std::bitset<1> private_indicator_;
  std::uint16_t section_length_;
  std::uint16_t source_id_;
  std::bitset<2> reserved2_;
  std::bitset<5> version_number_;
  std::bitset<1> current_next_indicator_;
  std::uint8_t section_number_;
  std::uint8_t last_section_number_;
  std::uint8_t protocol_version_;
  std::uint8_t num_events_in_section_;
  std::vector<EventInformationSection> sections_;
  std::uint32_t crc_;
};
} // namespace atsc
} // namespace dvb
} // namespace showsaver
