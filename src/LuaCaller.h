/*
cpp 调用lua函数用，简化接口，增加可读性
*/

#pragma once
#include "LuaResult.h"

class LuaCaller
{
private:
	lua_State* m_pState;
	int        m_numArgs;
	int        m_tb;
	bool       m_called;
	bool       m_is_exist_fun = false; //true表示有这个函数

public:
	LuaCaller(const char* fun_name);
	~LuaCaller();

    int GetArgsNum() {return m_numArgs;}
    void SetArgsNum(int args) { m_numArgs = args; }

    // 是否有这个函数
    bool IsExistFun();

	bool Call(LuaResult* result = NULL);
	bool Result(LuaResult &result);

	//附加参数
	template<typename T>
	LuaCaller& operator+=(T t) {
		return this->Arg(t);
	}

	template<typename T>
	LuaCaller& operator<<(T t) {
		return this->Arg(t);
	}
    
    template<typename T>
    LuaCaller& PushObject(T t) {
        luabridge::push(m_pState, t);
        ++m_numArgs;
        return *this;
    }

	inline bool operator() ()
	{
		return ExCall();
	}

	template <class P1>
	bool operator() (P1 p1) 
	{
		PushObject(p1);
		return ExCall();
	}

	template <class P1, class P2>
	bool operator() (P1 p1, P2 p2) 
	{
		PushObject(p1);
		PushObject(p2);
		return ExCall();
	}
	template <class P1, class P2, class P3>
	bool operator() (P1 p1, P2 p2, P3 p3)
	{
		PushObject(p1);
		PushObject(p2);
		PushObject(p3);
		return ExCall();
	}
	template <class P1, class P2, class P3, class P4>
	bool operator() (P1 p1, P2 p2, P3 p3, P4 p4)
	{
		PushObject(p1);
		PushObject(p2);
		PushObject(p3);
		PushObject(p4);
		return ExCall();
	}


private:

	bool ExCall();
	LuaCaller& Arg(int value);
	LuaCaller& Arg(const char* value);
	LuaCaller& Arg(double value);
	LuaCaller& Arg(bool value);
    LuaCaller& Arg(unsigned int value);
    LuaCaller& Arg(unsigned long value);
    LuaCaller& Arg(unsigned long long value);
    LuaCaller& Arg(const std::string& value);
    LuaCaller& Arg(long int value);
};