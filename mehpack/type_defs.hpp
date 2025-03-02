#pragma once

#include <cstddef>

namespace meh {

using Byte = unsigned char;

enum class Types : Byte {
    //VOID
    VOID        = 0xFF,

    //INT
    INT8        = 0x00,
    INT16       = 0x01,
    INT32       = 0x02,
    INT64       = 0x03,

    UINT8       = 0x04,
    UINT16      = 0x05,
    UINT32      = 0x06,
    UINT64      = 0x07,

    //FLOATING POINT
    FLOAT       = 0x08,
    DOUBLE      = 0x09,

    //BOOL
    BOOL        = 0x0A,

    //CHAR
    CHAR        = 0x0B,
};

};