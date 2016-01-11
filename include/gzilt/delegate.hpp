#ifndef GZILT_DELEGATE_HPP
#define GZILT_DELEGATE_HPP

#include <utility>

namespace gzilt {

template< typename FunctionSignature >
class Delegate;

template< typename ReturnType, typename... Arguments >
class Delegate< ReturnType(Arguments...) > {
    using FunctionPtrType = ReturnType(*)(const void *, Arguments...);

    FunctionPtrType delegated_function_;
    const void * this_ptr_;

    Delegate() = delete;
public:
    Delegate(FunctionPtrType delegated_function, const void* this_ptr) :
        delegated_function_(delegated_function),
        this_ptr_(this_ptr) {}
    template< typename... ForwardArguments >
    ReturnType invoke(ForwardArguments&&... arguments) const {
        return (*delegated_function_)(this_ptr_, std::forward<ForwardArguments>(arguments)...);
    }
    template< typename... ForwardArguments >
    ReturnType operator()(ForwardArguments&&... arguments) const {
        return invoke(std::forward<ForwardArguments>(arguments)...);
    }
};

namespace detail {

template< typename ReturnType, class T, typename... Arguments >
class DelegateMemberFunction {
    DelegateMemberFunction() = delete;
    template< ReturnType(T::*MemberFunction)(Arguments...) >
    static ReturnType caller(const void * object, Arguments... arguments) {
        auto callee = const_cast<T *> (static_cast<const T *>(object));
        return (callee->*MemberFunction)(arguments ...);
    }
public:
    template< ReturnType(T::*MemberFunction)(Arguments...) >
    static Delegate< ReturnType(Arguments...) > bind(T * object, bool /*unused*/ = false) {
        auto static_caller = &DelegateMemberFunction::caller<MemberFunction>;
        return Delegate< ReturnType(Arguments...) >(static_caller, static_cast<const void *>(object));
    }
};

template< typename ReturnType, class T, typename... Arguments >
class DelegateConstMemberFunction {
	DelegateConstMemberFunction() = delete;
	template< ReturnType(T::*ConstMemberFunction)(Arguments...) const >
	static ReturnType caller(const void * object, Arguments... arguments) {
		auto callee = static_cast<const T*>(object);
		return (callee->*ConstMemberFunction)(arguments...);
	}
public:
	template< ReturnType(T::*ConstMemberFunction)(Arguments...) const >
	static Delegate< ReturnType(Arguments...) > bind(T * object, bool /*unused*/ = false) {
		auto static_caller = &DelegateConstMemberFunction::caller<ConstMemberFunction>;
		return Delegate< ReturnType(Arguments...) >(static_caller, static_cast<const void*>(object));
	}
};

template< typename ReturnType, typename... Arguments >
class DelegateFreeFunction {
    DelegateFreeFunction() = delete;
    template< ReturnType(*FreeFunction)(Arguments... arguments) >
    static ReturnType caller(const void * /*unused*/, Arguments... arguments) {
        return (*FreeFunction)(arguments...);
    }
public:
    template< ReturnType(*FreeFunction)(Arguments... args) >
    static Delegate< ReturnType(Arguments...) > bind(bool /*unused*/ = false) {
        auto static_caller = &DelegateFreeFunction::caller<FreeFunction>;
        return Delegate< ReturnType(Arguments...) >(static_caller, nullptr);
    }
};

template< typename FunctionSignature >
struct DelegateMatcher;

template< typename ReturnType, class Class, typename... Arguments >
struct DelegateMatcher< ReturnType(Class::*)(Arguments...) > {
    using DelegateType = DelegateMemberFunction< ReturnType, Class, Arguments...>;
    DelegateMatcher() = delete;
};
template< typename ReturnType, class Class, typename... Arguments >
struct DelegateMatcher< ReturnType(Class::*)(Arguments...) const > {
	using DelegateType = DelegateConstMemberFunction< ReturnType, Class, Arguments...>;
	DelegateMatcher() = delete;
};
template< typename ReturnType, typename... Arguments >
struct DelegateMatcher< ReturnType(*)(Arguments...) > {
    using DelegateType = DelegateFreeFunction< ReturnType, Arguments...>;
    DelegateMatcher() = delete;
};

} // namespace:detail

} // namespace: gzilt

#define CREATE_DELEGATE_( target, ... ) \
    (gzilt::detail::DelegateMatcher< decltype(target) >::DelegateType::bind<target>(__VA_ARGS__))

#ifdef _MSC_VER
#define CREATE_DELEGATE CREATE_DELEGATE_
#else
#define CREATE_DELEGATE(...) CREATE_DELEGATE_( __VA_ARGS__, false )
#endif

#endif
