#include <fstream>
#include <sstream>
#include <string>

namespace showsaver {
namespace dvb {
class Record {
public:
  Record();
  Record(int adapter_number);
  void open(int adapter_number);
  static std::string record_name_from_adapter(int adapter_number);
  template <typename T> std::streamsize read(T &buffer) {
    record_file_.read(buffer.data(), buffer.size());
    return record_file_.gcount();
  }

private:
  int adapter_number_;
  std::ifstream record_file_;
};
}
}
