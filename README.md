# Delegate

[![Travis Status](https://travis-ci.org/kaidokert/cpp-delegate.svg?branch=master)](https://travis-ci.org/kaidokert/cpp-delegate) [![Appveyor Status](https://ci.appveyor.com/api/projects/status/6k3s500lbwlrc03e?svg=true)](https://ci.appveyor.com/project/kaidokert/cpp-delegate) [![Coverage Status](https://coveralls.io/repos/kaidokert/cpp-delegate/badge.svg?branch=master&service=github)](https://coveralls.io/github/kaidokert/cpp-delegate)

Elbert Mai's [generic callback/delegate](http://www.codeproject.com/Articles/136799/Lightweight-Generic-C-Callbacks-or-Yet-Another-Del), C++11 with no other dependencies except ``<utility>``. No exceptions/rtti/heap usage, and just about 100 lines of single header template code.

This is effectively a raw function pointer wrapped in a typesafe template and has no runtime code size or processing overhead with any of the compilers.

Implementation patterned after version from this [smart function pointer article](http://www.codeproject.com/Articles/995916/A-Smart-Function-Pointer) and https://github.com/reiver-dev/cppcallback

Use primarily through CREATE_DELEGATE macro:
```cpp
struct foo {
	bool bar(int param) {  }
};
bool baz(int param) { }

foo foo_instance;
auto delegate = CREATE_DELEGATE(&foo::bar, &foo_instance);
delegate(42);
delegate = CREATE_DELEGATE(&baz);
delegate(90210);
Delegate<bool(int)> call_me_maybe = delegate;
call_me_maybe(31337);
```

Built with maximum warnings on gcc, clang, msvc,  full test coverage

### TODO
* Add [Catch](https://github.com/philsquared/Catch) / [Lest](https://github.com/martinmoene/lest) tests
* add gcc/arm build
* add cpplint
