#ifndef CZX_FUNCTION_TRAITS_H_190312
#define CZX_FUNCTION_TRAITS_H_190312

#include<functional>
#include<tuple>

template<typename T>
struct functionTraits;

//普通函数
template<typename ReturnType, typename... ArgsType>
struct functionTraits<ReturnType(ArgsType...)>
{
public:
	enum 
	{ 
		ArgsCounts = sizeof...(ArgsType)
	};
	typedef ReturnType Function_Type(ArgsType...);
	typedef ReturnType Return_Type;
	using STL_Function_Type = std::function<Function_Type>;
	typedef ReturnType(*Pointer)(ArgsType...);

	template<size_t N>
	struct Args
	{
		static_assert(N < ArgsCounts, "index is out of range, index must less than sizeof Args");
		using Type = typename std::tuple_element<N, std::tuple<ArgsType...>>::type;
	};

	typedef std::tuple<std::remove_cv_t<std::remove_reference_t<ArgsType>>...> Tuple_Type;
	typedef std::tuple<std::remove_const_t<std::remove_reference_t<ArgsType>>...> Bare_Tuple_Type;
};

//函数指针
template<typename ReturnType, typename... ArgsType>
struct functionTraits<ReturnType(*)(ArgsType...)> : functionTraits<ReturnType(ArgsType...)> {};

//std::function
template <typename ReturnType, typename... ArgsType>
struct functionTraits<std::function<ReturnType(ArgsType...)>> : functionTraits<ReturnType(ArgsType...)> {};

//成员函数
#define MEMBER_FUNCTION_TRAITS(...)\
template <typename ReturnType, typename ClassType, typename... ArgsType>\
struct functionTraits<ReturnType(ClassType::*)(ArgsType...) __VA_ARGS__> : functionTraits<ReturnType(ArgsType...)>{};\
MEMBER_FUNCTION_TRAITS()
MEMBER_FUNCTION_TRAITS(const)
MEMBER_FUNCTION_TRAITS(volatile)
MEMBER_FUNCTION_TRAITS(const volatile)

//仿函数
template<typename Callable>
struct functionTraits : functionTraits<decltype(&Callable::operator())> {};


template <typename Function>
typename functionTraits<Function>::STL_Function_Type to_function(const Function& lambda)
{
	return static_cast<typename functionTraits<Function>::STL_Function_Type>(lambda);
}

template <typename Function>
typename functionTraits<Function>::STL_Function_Type to_function(Function&& lambda)
{
	return static_cast<typename functionTraits<Function>::STL_Function_Type>(std::forward<Function>(lambda));
}

template <typename Function>
typename functionTraits<Function>::Pointer to_function_pointer(const Function& lambda)
{
	return static_cast<typename functionTraits<Function>::Pointer>(lambda);
}

#endif