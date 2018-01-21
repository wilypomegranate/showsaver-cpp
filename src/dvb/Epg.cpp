#include "dvb/Epg.hpp"
#include <iostream>

namespace showsaver {
namespace dvb {
const int ATSC_BASE_PID = 0x1FFB;
Epg::Epg() : got_mgt_(false) {}

Epg::Epg(int adapter_number) : got_mgt_(false) {
  open(adapter_number);
}

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
  int chan_filter = 0xc7;
  int chan_filter_mask = 0xff;
  sct_param.filter.filter[0] = chan_filter;
  sct_param.filter.mask[0] = chan_filter_mask;

  if (ioctl(demux_device_, DMX_SET_FILTER, &sct_param) < 0) {
    throw DvbException(errno, std::system_category());
  }
  atsc::SystemTimeTableParser stt;
  atsc::MasterGuideTableParser mgt;
  atsc::EventInformationTableParser eit;
  std::vector<unsigned char> buf;
  // buf.resize(10);
  ssize_t size = 0;
  std::size_t s = 20;
  buf.resize(20);
  while (!got_mgt_) {
    size = read(demux_device_, buf.data(), buf.size());
    if (size > 0) {
      // std::cout.write(reinterpret_cast<const char *>(buf.data()),
      // buf.size());
      buf.resize(size);
      s = mgt.parse(*this, buf.data(), buf.size());
      // buf.erase(buf.begin(), buf.begin()+s);
      // std::cout << buf.size() << std::endl;
      // std::cout << std::endl;
    }
  }

  // Once eit tables are known, tune to the relevant ones to build the guide.

  // ::close(demux_device_);

  // if ((demux_device_ = ::open(demux_file.c_str(), O_RDWR)) < 0) {
  //   throw DvbException(errno, std::system_category());
  // }

  // for (auto&& table : eit_tables_) {
  //   std::cout << table.table_type_pid() << std::endl;
  // }
  for (auto&& table : eit_tables_) {
    if (table.table_type() < 256 || table.table_type() > 383) {
      continue;
    }
    if (ioctl(demux_device_, DMX_STOP) < 0) {
      throw DvbException(errno, std::system_category());
    }
    ::close(demux_device_);

    if ((demux_device_ = ::open(demux_file.c_str(), O_RDWR)) < 0) {
      throw DvbException(errno, std::system_category());
    }
    std::memset(&sct_param, 0, sizeof(struct dmx_sct_filter_params));
    sct_param.pid = table.table_type_pid();
    sct_param.flags = DMX_IMMEDIATE_START | DMX_CHECK_CRC;
    sct_param.timeout = 10000;
    int chan_filter = 0xcb;
    int chan_filter_mask = 0xff;
    sct_param.filter.filter[0] = chan_filter;
    sct_param.filter.mask[0] = chan_filter_mask;

    if (ioctl(demux_device_, DMX_SET_FILTER, &sct_param) < 0) {
      throw DvbException(errno, std::system_category());
    }

    // std::cout << table.table_type() << "\t" << table.table_type_pid()
    //           << std::endl;
    // for (int i = 0; i < 10000; i++) {
    size = 0;
    errno = 0;
    buf.resize(20);
    while (errno != ETIMEDOUT) {
      size = read(demux_device_, buf.data(), buf.size());
      if (size > 0) {

        // buf.resize(size);
        s = eit.parse(*this, buf.data(), buf.size());
        // std::cout.write(reinterpret_cast<const char*>(buf.data()), size);
        // std::cout << std::endl;
        // break;
      }
      // std::cout << size << "\t" << errno << std::endl;
    }
    // }
  }
}

void Epg::operator()(const atsc::MasterGuideTable& mgt) {
  eit_tables_ = mgt.tables();
  got_mgt_ = true;
}

void Epg::operator()(const atsc::EventInformationTable& eit) {
  for (auto&& section: eit.sections()) {
    std::cout << section.title_text();
    throw std::exception();
  }
  // eit_tables_ = mgt.tables();
  // got_mgt_ = true;
}

} // namespace dvb
} // namespace showsaver
