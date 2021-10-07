# HelloAddIn
HelloAddIn is an add-in example.  It exposes new JS APIs.  It also has a FormIt message listener and creates a new custom message.  For more information on Add-Ins, see [Creating an Add-In](https://formit3d.github.io/FormItExamplePlugins/docs/HowToBuild.html#CreatingAddIn).
To load this plugin, run this in the FormIt console-
```
FormIt.LoadPlugin("https://formit3d.github.io/HelloAddIn");
```
The console output window should then display-
```
Loaded: Hello AddIn
Registering HelloDLL JS functions from HelloDLL!!!
```
NOTE: AddIns are versioned and will only run on supported versions of FormIt.

To test this plugin, run the following commands-
```
console.log(HelloDLL.Test());
HelloDLL.Test2();
HelloDLL.TestArgs(true, 12);
var myclass= HelloDLL.GetMyClass();
console.log(JSON.stringify(myclass));
console.log(JSON.stringify(HelloDLL.PassMyClass(myclass)));
HelloDLL.NS2.Test();
HelloDLL.BROADCAST_kHelloAddIn();
```

Add-ins are just normal plugins that also load DLLs that expose new JavaScript APIs inside FormIt.  Add-ins specify the DLLs that are needed in the manifest in the ["DLLs"](https://github.com/FormIt3D/HelloAddIn/blob/main/v22_0/manifest.json#L8) property.
```
"DLLs" : ["PLUGINLOCATION/MyClass.dll", "PLUGINLOCATION/HelloDLL.dll"]
```
Since the DLLs are tied to specific versions of FormIt, it is versioned to only run on the specfic versions specified in the versions.json.  Note the usage of [these options](https://github.com/FormIt3D/HelloAddIn/blob/main/versions.json#L6) in the version object-
```
"lastVersion":true,
"exactVersion":true
```

The DLL directory contains the Visual Studio solution that genearates the DLLs needed by the add-in.
The project also needs a FormItSupport directory containing all the needed FormIt headers/libraries to build. FormItSupport can be found on the [Autodesk Developers Network](https://www.autodesk.com/developer-network/overview).

The solution builds two DLLs
- HelloDLL
    HelloDLL exposes the new javaScript APIs.
- MyClass
    MyClass DLL wraps the MyClass C++ class and shows how to convert to/from json
    to allow access through the JS API

When the solution is built, the DLLs end up in the top directory.  They then must be copied into the correct version directory for the version of FormIt.

Inside [HelloDLL.cpp](https://github.com/FormIt3D/HelloAddIn/blob/main/DLL/HelloDLL.cpp) is the code to register new JS APIs.

First [REGISTERAPIMETHODS](https://github.com/FormIt3D/HelloAddIn/blob/main/DLL/HelloDLL.cpp#L19) needs to wrap the new JS APIs. It also defines a function known to FormIt and is called when FormIt loads the DLLs.

Next declare a new Namespace, [REGISTERNAMESPACE](https://github.com/FormIt3D/HelloAddIn/blob/main/DLL/HelloDLL.cpp#L32), to put the new APIs into.

Each JS API has an [APIMETHOD](https://github.com/FormIt3D/HelloAddIn/blob/main/DLL/HelloDLL.cpp#L32).  See the [example code](https://github.com/FormIt3D/HelloAddIn/blob/main/DLL/HelloDLL.cpp) that is commented to explain how APIMETHOD works.
