# mehpack
A simple C++ [HEADER ONLY *wink wink*] binary archiving library with some qol features like debug name flags for variables

![screenshot](page_art/icon_art.png)

meh... it's good enough

### features
- template based packing for type deduction
- naming of packed variables to write under a DEBUG mode to catch any user errors while in development

### requirements
- C++23 or above (ideally i want to bring compatibility to C++17 and above)
- linked to C++ STL

# usage
this library is all headers, simply including mehpack.hpp will do the trick, there is also a cmake file included to create an interface to include the headers.

### logging
![screenshot](page_art/log.png)

mehpack defaults to logging with printf(), but you can bind your own logging callback! all you have to do is bing a function that takes in an std::string.
```C++
// for pure logging functions
meh::Global::set_logging_callback(log);
meh::Global::set_error_callback(error);

// for class method logging functions
meh::Global::set_logging_callback([&console](const std::string& message) { console->log(message); };
meh::Global::set_error_callback([&error](const std::string& message) { error->error(message); };
```

### packages
![screenshot](page_art/package.png)

mehpack is based around packages, you can pack stuff inside, and then get it's data and size to use as a range however you like!
```C++
meh::Package package(meh::PACK_DEBUG | meh::PACK_VERBOSE);
```
the flags you should keep note about are :
| Flag | Behaviour |
| --- | --- |
| `PACK_DEBUG` | writes debug information to file so we can analize it dynamically |
| `PACK_VERBOSE` | tries to log all possibly useful writing information |
| `PACK_SILENT` | avoids any and all kind of logging |
| `PACK_NOERR` | ignores errors |

you can write to a package like this:
```C++
uint8_t number = 8;
std::string str = "[>_<]";

package.pack("some number", number);
package.pack("some string", str);
```

then you can use the package data by obtaining the buffer data and the buffer size
```C++
std::ofstream out("out.bin", std::ios::binary);
out.write(reinterpret_cast<const char*>(package.data()), package.size());
out.close();
```

### enums
mehpack offers the MEH_MAKE_ENUM macro, this will create an enum and then also create an overload of enum_to_str() and str_to_enum() to permit mehpack to use the enum's litteral name in debug mode
```C++
MEH_ENUMTEMPLATE

// char here is our underlying type
MEH_MAKE_ENUM(SomeEnum, char,
  SOMETHING,
  WHATEVER,
  THING,
)

// enum_to_str(SomeEnum::WHATEVER) == "WHATEVER"
```
### !!! IMPORTANT !!!
the str_to_enum function needs to be defined in all used namespaces, so before using MEH_MAKE_ENUM you have to use MEH_ENUMTEMPLATE in every used namespace (including the global namespace)
