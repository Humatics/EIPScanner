include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(test test.cpp fanuc.cpp)
target_link_libraries(test EIPScanner)

if(WIN32)
  target_link_libraries(test ws2_32)
endif()
