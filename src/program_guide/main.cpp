#include "dvb/Epg.hpp"
#include <iostream>

using namespace showsaver;

int main(int argc, char **argv) {
  dvb::Frontend f;
  try {
    f.open(0);
    f.tune(575000000);
    // f.tune(593000000);
    dvb::Epg epg(0);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }

  return 0;
}
