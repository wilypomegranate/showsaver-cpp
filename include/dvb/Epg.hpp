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

private:
  int demux_device_;
};
}
}
