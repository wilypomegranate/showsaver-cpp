#include "dvb/Record.hpp"

namespace showsaver {
namespace dvb {
Record::Record() {}
Record::Record(int adapter_number) { open(adapter_number_); }
void Record::open(int adapter_number) {
  adapter_number_ = adapter_number;
  std::string dvr_file = record_name_from_adapter(adapter_number_);
  record_file_.open(dvr_file);
}
std::string Record::record_name_from_adapter(int adapter_number) {
  std::stringstream ss;
  ss << "/dev/dvb/adapter" << adapter_number << "/dvr" << adapter_number;
  return ss.str();
}
}
}
