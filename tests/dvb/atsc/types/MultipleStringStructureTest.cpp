#include "dvb/atsc/types/MultipleStringStructure.hpp"
#include <catch.hpp>
#include <fstream>
#include <iostream>

namespace atsc = showsaver::dvb::atsc;

unsigned char text[] = {0x01, 0x65, 0x6e, 0x67, 0x01, 0x00, 0x00, 0x10,
                        0x50, 0x61, 0x69, 0x64, 0x20, 0x50, 0x72, 0x6f,
                        0x67, 0x72, 0x61, 0x6d, 0x6d, 0x69, 0x6e, 0x67};
unsigned int text_len = 24;

TEST_CASE("MultipleStringStructure", "[MultipleStringStructure]") {
  std::vector<unsigned char> buffer(text, text + text_len);
  atsc::MultipleStringStructure m;
  m.init(buffer);
  REQUIRE(m.text() == "Paid Programming");
}
