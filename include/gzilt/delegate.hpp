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
	Delegate() = delete;
};

namespace detail {

template< typename ReturnType, class Class, typename... Arguments >
class DelegateMemberFunction {
	using TargetDelegate = Delegate< ReturnType(Arguments...) >;

    template< ReturnType(Class::*MemberFunction)(Arguments...) >
    static ReturnType caller(const void * this_ptr, Arguments... arguments) {
        auto callee = const_cast<Class *> (static_cast<const Class *>(this_ptr));
        return (callee->*MemberFunction)(arguments ...);
    }
public:
    template< ReturnType(Class::*MemberFunction)(Arguments...) >
    static Delegate< ReturnType(Arguments...) > bind(Class * this_ptr, bool /*unused*/ = false) {
        auto static_caller = &DelegateMemberFunction::caller<MemberFunction>;
        return TargetDelegate(static_caller, static_cast<const void *>(this_ptr));
    }
	DelegateMemberFunction() = delete;
};

template< typename ReturnType, class Class, typename... Arguments >
class DelegateConstMemberFunction {
	using TargetDelegate = Delegate< ReturnType(Arguments...) >;

	template< ReturnType(Class::*ConstMemberFunction)(Arguments...) const >
	static ReturnType caller(const void * this_ptr, Arguments... arguments) {
		auto callee = static_cast<const Class*>(this_ptr);
		return (callee->*ConstMemberFunction)(arguments...);
	}
public:
	template< ReturnType(Class::*ConstMemberFunction)(Arguments...) const >
	static Delegate< ReturnType(Arguments...) > bind(Class * this_ptr, bool /*unused*/ = false) {
		auto static_caller = &DelegateConstMemberFunction::caller<ConstMemberFunction>;
		return TargetDelegate(static_caller, static_cast<const void*>(this_ptr));
	}
	DelegateConstMemberFunction() = delete;
};

template< typename ReturnType, typename... Arguments >
class DelegateFreeFunction {
	using TargetDelegate = Delegate< ReturnType(Arguments...) >;

	template< ReturnType(*FreeFunction)(Arguments... arguments) >
    static ReturnType caller(const void * /*unused*/, Arguments... arguments) {
        return (*FreeFunction)(arguments...);
    }
public:
    template< ReturnType(*FreeFunction)(Arguments... arguments) >
    static Delegate< ReturnType(Arguments...) > bind(bool /*unused*/ = false) {
        auto static_caller = &DelegateFreeFunction::caller<FreeFunction>;
        return TargetDelegate(static_caller, nullptr);
    }
	DelegateFreeFunction() = delete;
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
