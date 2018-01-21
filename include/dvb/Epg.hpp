#include "dvb/Frontend.hpp"
#include "dvb/atsc/types/SystemTimeTableParser.hpp"
#include "dvb/atsc/types/MasterGuideTableParser.hpp"
#include "dvb/atsc/types/EventInformationTableParser.hpp"
// #include <libdvbv5/atsc_header.h>
#include <unistd.h>

namespace showsaver {
namespace dvb {
class Epg {
public:
  Epg();
  Epg(int adapter_number);
  void open(int adapter_number);
  void operator()(const atsc::MasterGuideTable& mgt);
  void operator()(const atsc::EventInformationTable& eit);

private:
  std::vector<atsc::PsipTable> eit_tables_;
  bool got_mgt_;
  bool got_eit_;
  int demux_device_;
};
}
}
