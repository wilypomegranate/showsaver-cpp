#include <system_error>

namespace showsaver {
namespace dvb {
class DvbException : public std::system_error {
public:
  DvbException(int ev, const std::error_category &ecat)
      : std::system_error(ev, ecat) {}

private:
  int errno_;
};
}
}
