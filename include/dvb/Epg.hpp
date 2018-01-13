#include "dvb/Frontend.hpp"
#include <libdvbv5/atsc_header.h>
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
