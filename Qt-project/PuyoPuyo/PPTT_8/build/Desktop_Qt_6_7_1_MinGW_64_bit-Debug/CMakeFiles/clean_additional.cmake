# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PPTT_8_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PPTT_8_autogen.dir\\ParseCache.txt"
  "PPTT_8_autogen"
  )
endif()
