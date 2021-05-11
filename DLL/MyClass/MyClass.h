#pragma once

#ifdef EXPORT_MYCLASS
#define MYCLASS_EXPORT __declspec(dllexport)
#else
#define MYCLASS_EXPORT __declspec(dllimport)
#endif

#include <string>

#include "json/ScriptJSONConverter.h"

class MyClass
{
    JSON_SPECIALIZATION_SUPPORT(MyClass)

public:
    MYCLASS_EXPORT MyClass() {}

private:
    bool m_Bool = true;
    int m_Int = 10;

    std::string m_Name = "MyClass";
};  // class MyClass

DECLARE_JSON_SPECIALIZATION(MYCLASS, MyClass);
