include(cmake/check-supported-flags.cmake)

set(LANG_FLAGS "-std=c++11 -fno-exceptions -fno-rtti")
set(WARN_FLAGS "-Wall -Wextra -pedantic -Weffc++")
set(MSVC_DISABLED_FLAGS "/wd4514 /wd4350 /wd4710 /wd4820 /wd4068 /wd4548 /wd4711")

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /WX ${MSVC_DISABLED_FLAGS}")
else()
  check_supported_flags(EXTRA_WARNINGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LANG_FLAGS} ${WARN_FLAGS} ${EXTRA_WARNINGS}")
endif()
