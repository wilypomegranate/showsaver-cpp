#include "dvb/Frontend.hpp"
#include <iostream>

namespace showsaver {
namespace dvb {

Frontend::Frontend() {}

Frontend::Frontend(int adapter_number) { open(adapter_number); }

void Frontend::open(int adapter_number) {
  std::string device_file = device_name_from_adapter(adapter_number);
  std::memset(&frontend_param_, 0, sizeof(struct dvb_frontend_parameters));
  if ((frontend_device_ = ::open(device_file.c_str(), O_RDWR | O_NONBLOCK)) <
      0) {
    throw DvbException(errno, std::system_category());
  }
  std::string demux_file = demux_name_from_adapter(adapter_number);
  if ((demux_device_ = ::open(demux_file.c_str(), O_RDWR)) < 0) {
    throw DvbException(errno, std::system_category());
  }

  if ((demux_audio_device_ = ::open(demux_file.c_str(), O_RDWR)) < 0) {
    throw DvbException(errno, std::system_category());
  }
}

void Frontend::tune(uint32_t frequency) {
  frontend_param_.frequency = frequency;
  frontend_param_.u.vsb.modulation = VSB_8;

  // uint32_t mstd;

  // if (check_frontend(frontend_device_, FE_ATSC, &mstd) < 0) {
  //   ::close(frontend_device_);
  //   return false;
  // }
  int ret = ioctl(frontend_device_, FE_SET_FRONTEND, &frontend_param_);

  if (ret < 0) {
    // throw std::system_error(errno, std::system_category());
    throw DvbException(errno, std::system_category());
  }
}

std::string Frontend::device_name_from_adapter(int adapter_number) {
  std::stringstream ss;
  ss << "/dev/dvb/adapter" << adapter_number << "/frontend" << adapter_number;
  return ss.str();
}

std::string Frontend::demux_name_from_adapter(int adapter_number) {
  std::stringstream ss;
  ss << "/dev/dvb/adapter" << adapter_number << "/demux" << adapter_number;
  return ss.str();
}

void Frontend::setup_demux(int video_pid, int audio_pid) {
  int buffersize = 64 * 1024;
  if (ioctl(demux_device_, DMX_SET_BUFFER_SIZE, buffersize) == -1) {
    throw DvbException(errno, std::system_category());
  }

  struct dmx_pes_filter_params pesfilter;
  std::memset(&pesfilter, 0, sizeof(struct dmx_pes_filter_params));
  pesfilter.pid = video_pid;
  pesfilter.input = DMX_IN_FRONTEND;
  pesfilter.output = DMX_OUT_TS_TAP;
  pesfilter.pes_type = DMX_PES_VIDEO;
  pesfilter.flags = DMX_IMMEDIATE_START;

  if (ioctl(demux_device_, DMX_SET_PES_FILTER, &pesfilter) < 0) {
    throw DvbException(errno, std::system_category());
  }

  std::memset(&pesfilter, 0, sizeof(struct dmx_pes_filter_params));
  pesfilter.pid = audio_pid;
  pesfilter.input = DMX_IN_FRONTEND;
  pesfilter.output = DMX_OUT_TS_TAP;
  pesfilter.pes_type = DMX_PES_AUDIO;
  pesfilter.flags = DMX_IMMEDIATE_START;

  if (ioctl(demux_audio_device_, DMX_SET_PES_FILTER, &pesfilter) < 0) {
    throw DvbException(errno, std::system_category());
  }
}
}
}
