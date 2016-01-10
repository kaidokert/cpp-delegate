macro(add_executable_coverage target src)
  string(LENGTH "${COVERAGE}" coverage_on)
  set(coverage_on ${coverage_on} CACHE BOOL "")
  if(${coverage_on})
    set(mutable_src ${src} "")
    string (REPLACE ";" ".gcno " gcno_files "${mutable_src}" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -ftest-coverage -fprofile-arcs -lgcov")
    add_executable(${target} ${src})
    add_custom_target(coverage
      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${target}
      COMMAND $ENV{GCOV} -o ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/ ${gcno_files}
      DEPENDS ${target}
      )
  endif()
endmacro()
