#include "dvb/Frontend.hpp"
#include <iostream>
#include <unistd.h>

using namespace showsaver;

int main(int argc, char **argv) {
  dvb::Frontend dvb;
  try {
    dvb.open(0);
    dvb.tune(575000000);
    dvb.setup_demux(49, 52);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  while (true) {
    sleep(1);
  }
  return 0;
}
