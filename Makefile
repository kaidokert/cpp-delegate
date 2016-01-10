-include cmake/compiler-flags.mk

CXXFLAGS+=-Iinclude

CXXFLAGS += -std=c++11 -fno-exceptions -fno-rtti
CXXFLAGS += -Wall -Wextra -pedantic -Weffc++
CXXFLAGS += $(CXX_ALL_WARNINGS)
COV_FLAGS += --coverage -ftest-coverage -fprofile-arcs -lgcov

clang%: CXXFLAGS+= $(CLANG_EXTRA_WARNINGS)
g++%: CXXFLAGS+= $(GCC_EXTRA_WARNINGS)

TARGETS=$(CXX)_sample

COV_TARGET=coverage_sample

$(COV_TARGET): CXXFLAGS+=$(COV_FLAGS)

$(TARGETS) $(COV_TARGET): src/sample.cpp
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

coverage: $(COV_TARGET)
	./$(COV_TARGET)

all: $(TARGETS)

clean:
	$(RM) $(TARGETS) $(COV_TARGET)

.PHONY: all
