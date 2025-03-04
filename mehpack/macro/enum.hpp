// ----------------------------------------------------
//  this source code is part of mehpack.
//  copyright : Viola Inserra (cool_cose)  
//  @WEBSITE -> https://cose.cool
//  @GITHUB  -> https://github.com/cool-cose/mehpack
//  @CONTACT :
//       email   -> violainserra@gmail.com
//       discord -> @cool_cose
//       twitter -> @cool_cose
// ------------------------------------------------------

#pragma once

#include <stdexcept>
#include <string_view>
#include <string>

#define __MRPRIV_MACROTOOL_PARENS ()

#define __MRPRIV_MACROTOOL_EXPAND(...) __MRPRIV_MACROTOOL_EXPAND_4(__MRPRIV_MACROTOOL_EXPAND_4(__MRPRIV_MACROTOOL_EXPAND_4(__MRPRIV_MACROTOOL_EXPAND_4(__VA_ARGS__))))
#define __MRPRIV_MACROTOOL_EXPAND_4(...) __MRPRIV_MACROTOOL_EXPAND_3(__MRPRIV_MACROTOOL_EXPAND_3(__MRPRIV_MACROTOOL_EXPAND_3(__MRPRIV_MACROTOOL_EXPAND_3(__VA_ARGS__))))
#define __MRPRIV_MACROTOOL_EXPAND_3(...) __MRPRIV_MACROTOOL_EXPAND_2(__MRPRIV_MACROTOOL_EXPAND_2(__MRPRIV_MACROTOOL_EXPAND_2(__MRPRIV_MACROTOOL_EXPAND_2(__VA_ARGS__))))
#define __MRPRIV_MACROTOOL_EXPAND_2(...) __MRPRIV_MACROTOOL_EXPAND_1(__MRPRIV_MACROTOOL_EXPAND_1(__MRPRIV_MACROTOOL_EXPAND_1(__MRPRIV_MACROTOOL_EXPAND_1(__VA_ARGS__))))
#define __MRPRIV_MACROTOOL_EXPAND_1(...) __VA_ARGS__

#define MR_MACRO_FOR_EACH(macro, ...) \
  __VA_OPT__(__MRPRIV_MACROTOOL_EXPAND(MR_MACRO_FOR_EACH_HELPER(macro, __VA_ARGS__)))

#define MR_MACRO_FOR_EACH_HELPER(macro, a1, ...) \
  macro(a1) \
  __VA_OPT__(MR_MACRO_FOR_EACH_AGAIN __MRPRIV_MACROTOOL_PARENS (macro, __VA_ARGS__))

#define MR_MACRO_FOR_EACH_AGAIN() MR_MACRO_FOR_EACH_HELPER

#define MEH_ENUMTEMPLATE template <typename T> constexpr T str_to_enum(std::string_view str);

namespace RS {
    template <typename T> constexpr T str_to_enum(std::string_view str);
}

#define __RSPRIV_ENUMTOOL_TO_ENUM_IF(enumval)                                           \
    if (str == #enumval) return enumval;

#define __RSPRIV_ENUMTOOL_TO_STR_CASE(enumval)                                          \
    case enumval: return #enumval;

#define MEH_MAKE_ENUM(name, under, ...)                                                 \
    enum class name : under { __VA_ARGS__ };                                            \
    inline std::string enum_to_str(name value) {                                        \
    using enum name;                                                                    \
        switch (value) {                                                                \
            MR_MACRO_FOR_EACH(__RSPRIV_ENUMTOOL_TO_STR_CASE, __VA_ARGS__)               \
            default: return "UNDEFINED";                                                \
        }                                                                               \
    }                                                                                   \
    template <> constexpr name str_to_enum<name>(std::string_view str) {                \
        using enum name;                                                                \
        MR_MACRO_FOR_EACH(__RSPRIV_ENUMTOOL_TO_ENUM_IF, __VA_ARGS__)                    \
        throw std::invalid_argument("invalid enum string (" #name ")");                 \
    }   