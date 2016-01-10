# Delegate

[![Travis Status](https://travis-ci.org/kaidokert/cpp-delegate?branch=master)](https://travis-ci.org/kaidokert/cpp-delegate) [![Appveyor Status](https://ci.appveyor.com/api/projects/status/6k3s500lbwlrc03e?svg=true)](https://ci.appveyor.com/project/kaidokert/cpp-delegate) [![Coverage Status](https://coveralls.io/repos/kaidokert/cpp-delegate/badge.svg)](https://coveralls.io/github/kaidokert/cpp-delegate)

Elbert Mai's [generic callback/delegate](http://www.codeproject.com/Articles/136799/Lightweight-Generic-C-Callbacks-or-Yet-Another-Del), C++11 with no other dependencies except ``<utility>``. No exceptions/rtti/heap usage, and just about 100 lines of code.

Implementation patterned after version from this [smart function pointer article](http://www.codeproject.com/Articles/995916/A-Smart-Function-Pointer) and https://github.com/reiver-dev/cppcallback

Built with maximum warnings on gcc, clang, msvc. Full test coverage to be added.

### TODO
* Add [Catch](https://github.com/philsquared/Catch) / [Lest](https://github.com/martinmoene/lest) tests
* add gcc/arm build
