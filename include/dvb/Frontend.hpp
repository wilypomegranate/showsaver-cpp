#include "DvbException.hpp"
#include <errno.h>
#include <fcntl.h>
#include <linux/dvb/dmx.h>
#include <linux/dvb/frontend.h>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>

// For memset
#include <cstring>

namespace showsaver {
namespace dvb {

class Frontend {
public:
  Frontend();
  Frontend(int adapter_number);
  void open(int adapter_number);
  void tune(uint32_t frequency);
  static std::string device_name_from_adapter(int adapter_number);
  static std::string demux_name_from_adapter(int adapter_number);
  void setup_demux(int video_pid, int audio_pid);

private:
  struct dvb_frontend_parameters frontend_param_;
  int frontend_device_;
  int demux_device_;
  int demux_audio_device_;
};
}
}
