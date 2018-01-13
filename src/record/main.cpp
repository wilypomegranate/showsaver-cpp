#include "dvb/Frontend.hpp"
#include "dvb/Record.hpp"
#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <tuple>

using namespace showsaver;
namespace po = boost::program_options;
namespace pt = boost::posix_time;

int main(int argc, char **argv) {

  int frequency = 0;
  int video_pid = 0;
  int audio_pid = 0;
  int duration = 0;
  pt::time_duration record_duration;

  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "produce help message")(
      "frequency,f", po::value<int>(&frequency)->required(),
      "Frequency to tune to in Hz.");
  desc.add_options()("video-pid,v", po::value<int>(&video_pid)->required(),
                     "Video filter pid.");
  desc.add_options()("audio-pid,a", po::value<int>(&audio_pid)->required(),
                     "Audio filter pid.");
  desc.add_options()("duration,d", po::value<int>(&duration)->required(),
                     "Duration in minutes.");

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  } catch (po::error &e) {
    std::cerr << "ERROR:" << e.what() << "\n\n";
    std::cerr << desc << "\n";
    return 1;
  }

  record_duration = pt::minutes(duration);

  pt::ptime now = pt::second_clock::local_time();
  pt::ptime end = now + record_duration;

  dvb::Frontend dvb;
  dvb::Record record;
  try {
    dvb.open(0);
    dvb.tune(frequency);
    dvb.setup_demux(video_pid, audio_pid);
    record.open(0);
    std::array<char, 4096> buffer;
    std::streamsize num_bytes = 0;
    while (now < end) {
      num_bytes = record.read(buffer);
      now = pt::second_clock::local_time();
      std::cout.write(buffer.data(), num_bytes);
    }
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  return 0;
}
