#include <array>

namespace showsaver {
namespace dvb {
namespace atsc {
template <class T, std::size_t N = 20> class SystemTimeTableParser {
public:
  SystemTimeTableParser(T callback_class);
  std::size_t parse(const std::array<unsigned char, N>);
  void parse_table_id(const std::array<unsigned char, N>);

private:
  T callback_class_;
  std::size_t current_pos_;
  std::size_t num_held_bytes_;
  std::array<unsigned char, N> held_bytes_;
};
}
}
}
