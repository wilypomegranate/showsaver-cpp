#include "dvb/Epg.hpp"
#include <iostream>

namespace showsaver {
namespace dvb {
const int ATSC_BASE_PID = 0x1FFB;
Epg::Epg() {}

Epg::Epg(int adapter_number) { open(adapter_number); }

void Epg::open(int adapter_number) {
  std::string demux_file = Frontend::demux_name_from_adapter(adapter_number);
  if ((demux_device_ = ::open(demux_file.c_str(), O_RDWR)) < 0) {
    throw DvbException(errno, std::system_category());
  }
  struct dmx_sct_filter_params sct_param;
  std::memset(&sct_param, 0, sizeof(struct dmx_sct_filter_params));
  sct_param.pid = ATSC_BASE_PID;
  sct_param.flags = DMX_IMMEDIATE_START;
  sct_param.timeout = 0;
  int chan_filter = 0xcd;
  int chan_filter_mask = 0xff;
  sct_param.filter.filter[0] = chan_filter;
  sct_param.filter.mask[0] = chan_filter_mask;

  if (ioctl(demux_device_, DMX_SET_FILTER, &sct_param) < 0) {
    throw DvbException(errno, std::system_category());
  }
  atsc::SystemTimeTableParser stt;
  std::vector<unsigned char> buf;
  // buf.resize(10);
  ssize_t size = 0;
  std::size_t s = 20;
  buf.resize(20);
  while (true) {
    size = read(demux_device_, buf.data(), buf.size());
    if (size > 0) {
      // std::cout << size << "\n";
      // std::cout.write(reinterpret_cast<const char *>(buf.data()), buf.size());
        s = stt.parse(*this, buf.data(), buf.size());
      // buf.erase(buf.begin(), buf.begin()+s);
      // std::cout << buf.size() << std::endl;
      // std::cout << std::endl;
    }
  }
}
}
}
