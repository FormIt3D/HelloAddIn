#pragma once

#ifdef EXPORT_MYCLASS
#define MYCLASS_EXPORT __declspec(dllexport)
#else
#define MYCLASS_EXPORT __declspec(dllimport)
#endif

#pragma warning(disable: 4251)
//#pragma warning(disable: 4273)

#include <string>

#include "json/ScriptJSONConverter.h"

#include "FormItCore/include/FormItMessaging.h"
#include "FormItCore/include/FormItCoreMessages.h"
#include "WSMScripting/IScriptInstance.h"
#include "FormItCore/include/FormItCoreAPIDLL.h"

namespace FormIt
{
    // Create a new message type for HelloAddIn
    // NOTE: Currently DECLARE_MESSAGE_VOID doesn't work.  It uses the wrong EXPORT
    //DECLARE_MESSAGE_VOID(kHelloAddIn);
    struct kHelloAddInType : public FormIt::MessageVoidStruct{
    std::string message() const override
        { return "FormIt.Message.kHelloAddIn"; }
    };
    // The new kHelloAddIn message type
    extern MYCLASS_EXPORT const kHelloAddInType kHelloAddIn;
};

// MyClass is an example class that can roundtrip C++ <-> JS
class MyClass : public FormIt::MessageListener
{
    JSON_SPECIALIZATION_SUPPORT(MyClass)

public:
    MYCLASS_EXPORT MyClass() {}

private:
    bool m_Bool = true;
    int m_Int = 10;

    std::string m_Name = "MyClass";

};  // class MyClass

// Prepare MyClass for conversion to JSON
DECLARE_JSON_SPECIALIZATION(MYCLASS, MyClass);

// MyMessageListener is an example class that's a MessageListener that can
// listen to FormIt messages.
class MyMessageListener : public FormIt::MessageListener
{
public:
    MYCLASS_EXPORT MyMessageListener(IScriptInstance* instance) : m_IScriptInstance(instance)
    {
        if (m_IScriptInstance)
            m_IScriptInstance->Evaluate("console.log(\"HelloAddIn: Subscribing to FormIt::kHelloAddIn\")");

        // Listen to our new kHelloAddIn messages
        Subscribe(FormIt::kHelloAddIn, [this](MessageStruct const&, MessagePayloadStruct const&)
            {
                if (m_IScriptInstance)
                    m_IScriptInstance->Evaluate("console.log(\"HelloAddIn: Received FormIt::kHelloAddIn message!!!\")");
            });

        // Listen to FormIt::kCameraOperationStarted messages
        Subscribe(FormIt::kCameraOperationStarted, [this](MessageStruct const&, MessagePayloadStruct const&)
            {
                if (m_IScriptInstance)
                    m_IScriptInstance->Evaluate("console.log(\"HelloAddIn: Received FormIt::kCameraOperationStarted message!!!\")");
            });
    }

    // Hack, but it's just an example.
    IScriptInstance* m_IScriptInstance = nullptr;
};  // class MyMessageListener

