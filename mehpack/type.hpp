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
#include "constraints.hpp"

namespace meh {

// byte definition is using unsigned char for maximum compatibility
// we really shouldn't need to use std::byte but if we do we can
// just change the Byte definition right here
using Byte          = unsigned char;

// int definitions
// these should always be assured to be the reported size
using int8      = signed char;
using int16     = short;
using int32     = int;
using int64     = long long;

using uint8     = unsigned char;
using uint16    = unsigned short;
using uint32    = unsigned int;
using uint64    = unsigned long long;

// we hold all types we may need to switch logic for right here
// some special cases in this enum are:
// -    VOID is always going to be 0xFF (255)
// -    the first digit of the id represents the larger group while the second digits specifies its size
//      (larger groups are types that directly compare to eachother and just differ in size)
//      the groups are:
//      -   INT     -> 0
//      -   FLOAT   -> 1
//      -   BOOL    -> 2
//      -   CHAR    -> 3
enum class NumType : Byte {
    VOID        = 0xFF,

    INT8        = 0x00,
    INT16       = 0x01,
    INT32       = 0x02,
    INT64       = 0x03,

    UINT8       = 0x04,
    UINT16      = 0x05,
    UINT32      = 0x06,
    UINT64      = 0x07,

    FLOAT       = 0x10,
    DOUBLE      = 0x11,

    BOOL        = 0x20,

    CHAR        = 0x30,
    STRING      = 0x31,

    ENUM        = 0x40,

    OBJECT      = 0x50,
};

// returns the name of an enumerated type as a string.
// this should be the only case of hard coded enum to string conversion,
// all other cases should use the MAKE_ENUM API macro
inline std::string numtype_to_str(const NumType& num) {
    using enum NumType;
    switch(num) {
        case VOID:      return "VOID";                                      
        case INT8:      return "INT8";                      
        case INT16:     return "INT16";                     
        case INT32:     return "INT32";                     
        case INT64:     return "INT64";                     
        case UINT8:     return "U_INT8";                     
        case UINT16:    return "U_INT16";                    
        case UINT32:    return "U_INT32";                    
        case UINT64:    return "U_INT64";                    
        case FLOAT:     return "FLOAT";                          
        case DOUBLE:    return "DOUBLE";                         
        case BOOL:      return "BOOL";                           
        case CHAR:      return "CHAR";                           
        case STRING:    return "STRING";     
        case ENUM:      return "ENUM";
        case OBJECT:    return "OBJECT";
    }
}

// converts a specific type to its equivalent byte
template<typename T> requires (std::is_same_v<T, void>)         inline NumType type_to_num() { return NumType::VOID; }
template<typename T> requires (std::is_same_v<T, int8>)         inline NumType type_to_num() { return NumType::INT8; }
template<typename T> requires (std::is_same_v<T, int16>)        inline NumType type_to_num() { return NumType::INT16; }
template<typename T> requires (std::is_same_v<T, int32>)        inline NumType type_to_num() { return NumType::INT32; }
template<typename T> requires (std::is_same_v<T, int64>)        inline NumType type_to_num() { return NumType::INT64; }
template<typename T> requires (std::is_same_v<T, uint8>)        inline NumType type_to_num() { return NumType::UINT8; }
template<typename T> requires (std::is_same_v<T, uint16>)       inline NumType type_to_num() { return NumType::UINT16; }
template<typename T> requires (std::is_same_v<T, uint32>)       inline NumType type_to_num() { return NumType::UINT32; }
template<typename T> requires (std::is_same_v<T, uint64>)       inline NumType type_to_num() { return NumType::UINT64; }
template<typename T> requires (std::is_same_v<T, float>)        inline NumType type_to_num() { return NumType::FLOAT; }
template<typename T> requires (std::is_same_v<T, double>)       inline NumType type_to_num() { return NumType::DOUBLE; }
template<typename T> requires (std::is_same_v<T, bool>)         inline NumType type_to_num() { return NumType::BOOL; }
template<typename T> requires (std::is_same_v<T, char>)         inline NumType type_to_num() { return NumType::CHAR; }
template<typename T> requires (meh::constraint::is_string<T>)   inline NumType type_to_num() { return NumType::STRING; }

// returns the size of a type from its enumerator
// if the size of a type is impossible to know statically 0 will be returned
inline size_t get_type_size_from_enum(const NumType& num) {
    using enum NumType;
    switch(num) {
        case VOID:      return 0;                                      
        case INT8:      return sizeof(meh::int8);                      
        case INT16:     return sizeof(meh::int16);                     
        case INT32:     return sizeof(meh::int32);                     
        case INT64:     return sizeof(meh::int64);                     
        case UINT8:     return sizeof(meh::uint8);                     
        case UINT16:    return sizeof(meh::uint16);                    
        case UINT32:    return sizeof(meh::uint32);                    
        case UINT64:    return sizeof(meh::uint64);                    
        case FLOAT:     return sizeof(float);                          
        case DOUBLE:    return sizeof(double);                         
        case BOOL:      return sizeof(bool);                           
        case CHAR:      return sizeof(char);                           
        case STRING:    return 0;  
        case ENUM:      return 0; 
        case OBJECT:    return 0;
    }
}

// flag types related to packing data
using PackFlags = uint8;    // for now 8 flags should do it

static constexpr PackFlags PACK_DEBUG           = 1 << 0;   // write with debug symbols
static constexpr PackFlags PACK_VERBOSE         = 1 << 1;   // log out all useful info
static constexpr PackFlags PACK_SILENT          = 1 << 2;   // never log anything but errors
static constexpr PackFlags PACK_NOERR           = 1 << 3;   // never report errors

} // namespace meh
