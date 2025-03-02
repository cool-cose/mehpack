# mehpack
A simple C++ [HEADER ONLY *wink wink*] binary archiving library with some qol features like debug name flags for variables

![screenshot](icon_art.png)

meh... it's good enough

### features
- template based packing fortype deduction
- naming of packed variables to write under a DEBUG mode to catch any user errors while in development

### requirements
- C++23 or above (ideally i want to bring compatibility to C++17 and above)
- linked to C++ STL

### usage
this library is all headers, simply including mehpack.hpp will do the trick, there is also a cmake file included to create an interface to include the headers.
