#include"functionTraits.h"
#include<iostream>
using namespace std;

typedef void(*FUNC)(int, int);
///////////////////////////////////////////////////////////
//函数提供模块
////////////////////////////////////////////////////////////
void print(int a, int b)
{
	cout << "a=" << a << " b=" << b << endl;
}

FUNC pPrint = print;

class Test
{
public:
	Test(int a) :m_a(a) {}
	void test(int b)
	{
		cout << "test:" << a + b << endl;
	}
private:
	int m_a;
}

struct CallObject
{
	void operator()()
	{
		cout << "CallObject" << endl;
	}
};
///////////////////////////////////////////////////////////
//test module
//////////////////////////////////////////////////////////
void TestNormalFunction()
{
	auto func = to_function(print);
	cout << "args:" << functionTraits<decltype(print)>::ArgsCounts << endl;
	functionTraits<decltype(print)>::Args<0>::Type value = 10;//获取参数类型
	cout << "value:" << value << endl;
	cout << typeid(func).name() << endl;
	func(1, 2);
	auto pFunc = to_function_pointer(print);//转换函数指针
	cout << typeid(pFunc).name() << endl;
	pFunc(1, 2);
}

void TestFuncPointer()
{
	auto func = to_function(pPrint);
	cout << "args:" << functionTraits<decltype(print)>::ArgsCounts << endl;
	functionTraits<decltype(print)>::Args<0>::Type value = 10;//获取参数类型
	cout << "value:" << value << endl;
	cout << typeid(func).name() << endl;
	func(1, 1);
}

void TestSTLFunction()
{
	std::function<void(int)> func = print;
	//std::function<void(int)> func = std::bind(print, std::placeholders::_1);
	auto _func = to_function(func);
	cout << "args:" << functionTraits<decltype(print)>::ArgsCounts << endl;
	functionTraits<decltype(print)>::Args<0>::Type value = 10;//获取参数类型
	cout << "value:" << value << endl;
	cout << typeid(_func).name() << endl;
	_func(1, 2);
}


//直接根据参数调用
template<typename ReturnType, typename ClassType, typename...Args>
void  helpToFunction(ReturnType(ClassType::*f)(Args...), ClassType& obj, Args&&...args)
{
	std::function<ReturnType(Args...)> func = [&obj, f, &args...](Args...) {
		return (obj.*f)(std::forward<Args>(args)...);
	};
	func(std::forward<Args>(args)...);
}

//返回可调用实体
template<typename ReturnType, typename ClassType, typename...Args>
std::function<ReturnType(Args...)>  helpToFunction(ReturnType(ClassType::*f)(Args...), ClassType& obj)
{
	std::function<ReturnType(Args...)> func = [&obj, f](Args&&...args) {
		return (obj.*f)(std::forward<Args>(args)...);
	};
	//func(std::forward<Args>(args)...);
	return func;
}

void TestMemberFunction()
{
	Test t(1);

	//方法一：通过helpToFunction函数 将成员函数调用封装为lambda,自动转换为std::function
	// helpToFunction(&Test::test, t, 2);
	// helpToFunction(&Test::test, t)(2);

	//方法二：直接包装函数
	auto func = to_function(&Test::test, t);//转换为std::function
	cout << "args:" << functionTraits<decltype(print)>::ArgsCounts << endl;
	functionTraits<decltype(print)>::Args<0>::Type value = 10;//获取参数类型
	cout << "value:" << value << endl;
	cout << typeid(func).name() << endl;
	func(2);
}

void TestFunctionObject()
{
	auto func = to_function(CallObject());
	func();
}