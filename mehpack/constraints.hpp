// ----------------------------------------------------
//  this source code is part of mehpack.
//  copyright : Viola Inserra (cool_cose)  
//  @WEBSITE -> https://cose.cool
//  @GITHUB  -> https://github.com/cool-cose/mehpack
//  @CONTACT :
//       email   -> violainserra@gmail.com
//       discord -> @cool_cose
//       twitter -> @cool_cose
// ----------------------------------------------------

#pragma once

// this file contains constraits for our templates for nicer errors and linting
// if C++17 support is added this will also include the same versions of ours
// constraints as type traits instead of C++20 concepts.
// any other code that uses the concepts will also need a version using traits.

#include <string>

namespace meh::constraint {

template<typename T>
concept is_sint =
    std::is_same_v<T,   signed char>    ||
    std::is_same_v<T,   short>          ||
    std::is_same_v<T,   int>            ||
    std::is_same_v<T,   long long>      ;
template<typename T>
concept is_uint =
    std::is_same_v<T,   unsigned char>      ||
    std::is_same_v<T,   unsigned short>     ||
    std::is_same_v<T,   unsigned int>       ||
    std::is_same_v<T,   unsigned long long> ;
template<typename T>
concept is_int =
    meh::constraint::is_sint<T> ||
    meh::constraint::is_uint<T>;
    
template<typename T>
concept is_c_string = 
    std::is_convertible_v<T,   const char*>;
template<typename T>
concept is_cpp_string =
    std::is_same_v<T,   std::string>    ;
template<typename T>
concept is_string =
    meh::constraint::is_c_string<T>     ||
    meh::constraint::is_cpp_string<T>   ;

template<typename T>
concept is_basic_packageable =
    std::is_same_v<T,   float>      ||
    std::is_same_v<T,   double>     ||
    std::is_same_v<T,   bool>       ||
    std::is_same_v<T,   char>       ||
    meh::constraint::is_int<T>      ;
template<typename T>
concept is_packageable =
    is_basic_packageable<T> ||
    is_string<T>            ;

} // namespace meh