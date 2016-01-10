EXCLUDED_WARNINGS +=              \
  -Wsystem-headers                \
  -Wabi                           \
  -Waggregate-return

GCC_EXTRA_WARNINGS +=             \
  -Wabi-tag                       \
  -Wconditionally-supported       \
  -Wdouble-promotion              \
  -Wlogical-op                    \
  -Wnoexcept                      \
  -Wstrict-null-sentinel          \
  -Wsuggest-attribute=const       \
  -Wsuggest-attribute=format      \
  -Wsuggest-attribute=noreturn    \
  -Wsuggest-attribute=pure        \
  -Wtrampolines                   \
  -Wunsafe-loop-optimizations     \
  -Wuseless-cast                  \
  -Wvector-operation-performance  \
  -Wzero-as-null-pointer-constant

CLANG_EXTRA_WARNINGS +=           \
  -Weverything                    \
  -Wno-c++98-compat               \
  -Wno-c++98-compat-pedantic      \
  -Wno-unknown-pragmas

CXX_ALL_WARNINGS +=               \
  -Wctor-dtor-privacy             \
  -Wconversion                    \
  -Wcast-align                    \
  -Wcast-qual                     \
  -Wdate-time                     \
  -Wdisabled-optimization         \
  -Werror                         \
  -Wfloat-conversion              \
  -Wfloat-equal                   \
  -Wformat-nonliteral             \
  -Wformat-security               \
  -Wformat-y2k                    \
  -Winline                        \
  -Wmissing-braces                \
  -Wmissing-declarations          \
  -Wold-style-cast                \
  -Woverloaded-virtual            \
  -Wpadded                        \
  -Wpacked                        \
  -Wredundant-decls               \
  -Wshadow                        \
  -Wsign-conversion               \
  -Wsign-promo                    \
  -Wstack-protector               \
  -Wswitch-default                \
  -Wswitch-enum                   \
  -Wsynth                         \
  -Wunused-macros
