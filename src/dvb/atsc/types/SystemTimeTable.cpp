#include "dvb/atsc/types/SystemTimeTable.hpp"

namespace showsaver {
namespace dvb {
namespace atsc {
SystemTimeTable::SystemTimeTable() {}
const std::uint8_t SystemTimeTable::get_table_id() const { return table_id; }
void SystemTimeTable::set_table_id(const std::uint8_t table_id) {
  this->table_id = table_id;
}
}
}
}
