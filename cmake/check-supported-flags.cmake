include(CheckCXXSourceCompiles)

include(cmake/compiler-flags.cmake)

macro(check_supported_flags OUTPUT_VAR)
  foreach(flag ${GCC_EXTRA_WARNINGS} ${CLANG_EXTRA_WARNINGS})
    set(CMAKE_REQUIRED_DEFINITIONS "-W${flag}")
    string(REPLACE "=" "-" result_var "flag-${flag}-result" )
    string(REPLACE "+" "__" result_var ${result_var})
    CHECK_CXX_SOURCE_COMPILES("int main() { return 0; }" ${result_var}
      FAIL_REGEX "nrecognized.*option|unknown.*option|not supported")
    if(${result_var})
      list(APPEND CXX_ALL_WARNINGS "${flag}")
    endif()
  endforeach()

  # flatten the list
  list(INSERT CXX_ALL_WARNINGS 0 "")
  string (REPLACE ";" " -W" ${OUTPUT_VAR} "${CXX_ALL_WARNINGS}")
endmacro()
