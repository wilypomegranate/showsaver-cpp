cmake_minimum_required(VERSION 3.1.0)
project(showsaver)

set (CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

find_package(Boost 1.55.0 REQUIRED)

find_package(Boost COMPONENTS program_options REQUIRED)

find_package(PkgConfig REQUIRED)

include_directories(
  "include"
  thirdparty/catch2/include
  )

add_executable(tuner src/tuner/main.cpp src/dvb/Frontend.cpp)
add_executable(record src/record/main.cpp src/dvb/Frontend.cpp src/dvb/Record.cpp)
add_executable(program_guide src/program_guide/main.cpp src/dvb/Epg.cpp src/dvb/Frontend.cpp src/dvb/utils/ParserUtils.cpp src/dvb/atsc/types/SystemTimeTable.cpp src/dvb/atsc/types/SystemTimeTableParser.cpp src/dvb/atsc/types/MasterGuideTable.cpp src/dvb/atsc/types/EventInformationTable.cpp src/dvb/atsc/types/MultipleStringStructure.cpp)

add_executable(tests tests/main.cpp tests/dvb/atsc/types/MultipleStringStructureTest.cpp src/dvb/atsc/types/MultipleStringStructure.cpp src/dvb/utils/ParserUtils.cpp)

target_link_libraries(
  record
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  )
