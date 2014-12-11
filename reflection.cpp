
#include "stdafx.h"
#include "iostream"
#include "string"
#include "map"
#include "typeinfo"
#define REF
#ifdef REF

#define addFUNC(className) ref[_toName(className)] = className::createObject
#define _toName(name) #name
#define initMethod(name) ref_m[_toName(name)] = name
#define _addMethod(name) this->_methods[name] = ref_m[name]

typedef void (*m_ptr)();
std::map<std::string, m_ptr> ref_m;

#endif
class Base
{

protected:
	Base(){};
	virtual ~Base(){};

#ifdef REF
	std::map<std::string, m_ptr> _methods;
#endif

public:
	
	static Base* createObject()
	{
		auto p = new Base();
		return p;
	}

	virtual void print()
	{
		std::cout << "Base" << std::endl;
	}

#ifdef REF

	void addMethod(std::string str)
	{
		_addMethod(str);
	}

	auto getMethod(std::string str)->decltype(_methods[str])
	{
		return _methods[str];
	}

#endif
};

class A : public Base
{
public:

	static Base* createObject()
	{
		auto p = new A();
		return p;
	}

	virtual void print()
	{
		std::cout << "A" << std::endl;
	}

protected:

	A(){};
	virtual ~A(){};
};
class B : public Base
{
public:

	static Base* createObject()
	{
		auto p = new B();
		return p;
	}

	virtual void print()
	{
		std::cout << "B" << std::endl;
	}

protected:

	B(){};
	virtual ~B(){};
};

#ifdef REF

typedef Base* (*ptr)();
std::map<std::string, ptr> ref;

auto getClass(std::string str) -> decltype(ref[str]())
{
	return ref[str]();
}

void fuck1()
{
	std::cout << "fuck1" << std::endl;
}

void fuck2()
{
	std::cout << "fuck2" << std::endl;
}

void initMap()
{
	addFUNC(Base);
	addFUNC(A);
	addFUNC(B);

	initMethod(fuck1);
	initMethod(fuck2);
}

#endif

int main(int argc, _TCHAR* argv[])
{
	initMap();
	std::string in;
	while (std::cin >> in)
	{
		if (in == "end") break;
		if (ref.find(in) != ref.end())
		{
			auto p = getClass(in);
			p ->print();
		}
		else
		{
			std::cout << "error" << std::endl;
		}
	}
	auto p = getClass("Base");
	p->print();
	std::cin >> in;
	p->addMethod(in);
	std::cin >> in;
	auto m = p->getMethod(in);
	if (m != nullptr)
	{
		m();
	}
	else
	{
		std::cout << "mis" << std::endl;
	}
	system("pause");
	return 0;
}

