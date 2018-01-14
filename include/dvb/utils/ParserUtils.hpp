#include <boost/crc.hpp>
#include <cstdint>

namespace showsaver {
namespace dvb {
namespace utils {
bool validate_crc_32(const unsigned char *, std::size_t, uint32_t);
}
}
}
