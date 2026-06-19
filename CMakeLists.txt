cmake_minimum_required(VERSION 3.10)

project(ARPGuard)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

add_executable(
    arpguard
    src/main.cpp
    src/sniffer.cpp
    src/parser.cpp
)

target_include_directories(
    arpguard PRIVATE include
)

target_link_libraries(
    arpguard
    ${PCAP_LIBRARIES}
)
