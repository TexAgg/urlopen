CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
project("urlopen")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/simpleini)

add_library(urlfile urlfile.cpp urlfile.hpp)

add_executable(urlopen main.cpp)
target_link_libraries(urlopen urlfile)

file(COPY setup.sh DESTINATION ${PROJECT_BINARY_DIR})

file(COPY twitter.com.url DESTINATION ${PROJECT_BINARY_DIR})
enable_testing()
# This should open "https://twitter.com/search-advanced" in your browser.
add_test(twitter urlopen "twitter.com.url")

install(TARGETS urlopen DESTINATION /usr/local/bin)
install(FILES urlopen.desktop DESTINATION /usr/share/applications)
install(FILES urlopen.1 DESTINATION /usr/local/man/man1)
install(FILES img/urlopen_64x64.png DESTINATION /usr/share/pixmaps)
install(FILES img/application-x-mswinurl.svg DESTINATION /usr/share/icons/Humanity/mimes/256)