#pragma once

#include "dvb/utils/ParserUtils.hpp"
#include <string>
#include <vector>

namespace showsaver {
namespace dvb {
namespace atsc {
class MultipleStringStructure {
public:
  MultipleStringStructure();
  std::uint16_t init(const std::vector<unsigned char>&);

private:
  std::string text_;
};
} // namespace atsc
} // namespace dvb
} // namespace showsaver
