#include <boost/crc.hpp>
#include <cstdint>
#include <vector>

namespace showsaver {
namespace dvb {
namespace utils {
bool validate_crc_32(const unsigned char *, std::size_t, uint32_t);
std::uint16_t parse_header(const std::vector<unsigned char> &, std::uint8_t &,
                           std::uint16_t &);

void parse_uint16_t(std::vector<unsigned char>::const_iterator position, std::uint16_t& data);
void parse_uint32_t(std::vector<unsigned char>::const_iterator position, std::uint32_t& data);

}}}
