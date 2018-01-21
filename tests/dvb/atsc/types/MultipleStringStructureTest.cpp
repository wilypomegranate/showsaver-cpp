#include "dvb/atsc/types/MultipleStringStructure.hpp"
#include <catch.hpp>
#include <fstream>
#include <iostream>

namespace atsc = showsaver::dvb::atsc;

void load_test_data(std::vector<unsigned char>&buffer, const std::string& filename) {
  std::ifstream ifs(filename.c_str(), std::ios::binary | std::ios::ate);
  if (!ifs.good()) {
    throw std::exception();
  }
  std::streamsize size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  std::vector<char> tmp;
  tmp.resize(size);
  ifs.read(tmp.data(), size);
  buffer = std::vector<unsigned char>(tmp.begin(), tmp.end());
}

TEST_CASE("MultipleStringStructure", "[MultipleStringStructure]") {
  std::vector<unsigned char> buffer;
  load_test_data(buffer, "/tmp/foo");
  atsc::MultipleStringStructure m;
  // std::cout.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
  // std::cout << std::endl;
  m.init(buffer);
  // REQUIRE(1 == 2);
}
