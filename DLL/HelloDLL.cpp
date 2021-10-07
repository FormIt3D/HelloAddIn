#include "pch.h"

#include <sstream>

#ifdef max
#undef max
#endif

#pragma warning(disable: 4251)

#include "FormItSupport/FormItCore/include/FormItMessaging.h"
#include "FormItSupport/WSMScripting/IScriptInstance.h"
#include "MyClass/MyClass.h"

// MyClass used in JS API below
static MyClass sMyClass;

// FormIt looks for REGISTERAPIMETHODS to load new JS APIs
REGISTERAPIMETHODS
{
    if (!scriptInstance)
        return;

    scriptInstance->Evaluate("console.log(\"Init MyMessageListener\")");
    static MyMessageListener sListener(scriptInstance);

    // Example to call JS code during registration
    scriptInstance->Evaluate("console.log(\"Registering HelloDLL JS functions from HelloDLL!!!\")");

    // Add new JS APIs
    // Declare the new "Namespace" to put the new APIs into.
    REGISTERNAMESPACE("HelloDLL")

    // Adding the JS API HelloDLL.Test() that takes no arguments.
    APIMETHOD(HelloDLL, Test, "")
    {
        return "HelloDLL.Test called!";
    });

    // Adding the JS API HelloDLL.Test2() that takes no arguments.
    APIMETHOD(HelloDLL, Test2, "")
    {
        // Example to call JS code
        scriptInstance->Evaluate("console.log(\"HelloDLL.Test2 JS function called from HelloDLL!!!\")");
        return JSON_UNDEFINED;
    });

    // Adding the JS API HelloDLL.TestArgs(arg1, arg2) that takes two arguments.
    APIMETHOD(HelloDLL, TestArgs, "arg1, arg2")
    {
        // NOTE: The arg names above ^^^^ have to match the args in the macros below.
        // arg1 expects a bool
        SCRIPTCONVERTER(bool, arg1);
        // arg2 expects an int
        SCRIPTCONVERTER(int, arg2);

        std::stringstream ss;
        std::string arg1Str = arg1 ? std::string("true") : std::string("false");
        ss << "Got arg1: " << arg1Str << " arg2: " << arg2;
        // Example to call JS code
        std::string cmd = "console.log(\"" + ss.str() + std::string("\")");
        scriptInstance->Evaluate(cmd);
        return JSON_UNDEFINED;
    });

    // HelloDLL.GetMyClass() returns sMyClass.
    // This uses DEFINE_JSON_TO_SPECIALIZATION/DEFINE_JSON_FROM_SPECIALIZATION
    // to convert to/from json
    APIMETHOD(HelloDLL, GetMyClass, "")
    {
        return to_json(sMyClass);
    });

    // Broadcast the new kHelloAddIn message
    APIMETHOD(HelloDLL, BROADCAST_kHelloAddIn, "")
    {
        BROADCAST(FormIt::kHelloAddIn);
        return JSON_UNDEFINED;
    });

    // HelloDLL.PassMyClass(myClass) expects a MyClass json object
    APIMETHOD(HelloDLL, PassMyClass, "myClass")
    {
        SCRIPTCONVERTER(MyClass, myClass);
        return to_json(myClass);
    });

    // Register a new Namespace inside HelloDLL
    REGISTERNAMESPACE("HelloDLL.NS2")

    // Add a new JS API inside NS2
    // Add JS API HelloDLL.NS2.Test();
    APIMETHOD(HelloDLL.NS2, Test, "")
    {
        // Example to call JS code
        scriptInstance->Evaluate("console.log(\"HelloDLL.NS2.Test2 JS function called from HelloDLL!!!\")");
        return JSON_UNDEFINED;
    });
}
