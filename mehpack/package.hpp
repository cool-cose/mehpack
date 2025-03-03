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
#include "type.hpp"
#include "global.hpp"
#include "buffer.hpp"

// !!! IMPORTANT !!!
// the packaging layout as of v0.1_r1 is:
//      with debug:
//      [NAME LENGTH][NAME STRING][TYPE][DATA]
//      without debug:
//      [TYPE][DATA]

namespace meh {

using Flags = uint8;

static constexpr Flags PACK_DEBUG           = 1 << 0;
static constexpr Flags PACK_VERBOSE         = 1 << 1;
static constexpr Flags PACK_SILENT          = 1 << 2;
static constexpr Flags PACK_NOERR           = 1 << 3;

static constexpr Byte DEBUG_BYTE            = 0xDD;
static constexpr Byte RELEASE_BYTE          = 0xAA;

class Package {
private:
    Flags _flags = std::numeric_limits<Flags>::min();
    meh::BinaryBuffer _buffer;

    void __write_metadata() {
        if (_flags & PACK_DEBUG)
            _buffer.insert(_buffer.end(), DEBUG_BYTE);
        else _buffer.insert(_buffer.end(), RELEASE_BYTE);
    }

public:
    Package() { __write_metadata(); }
    Package(uint8 flags) : _flags(flags) { __write_metadata(); }

    meh::Byte* get_data() { return _buffer.data(); }
    size_t get_size() { return _buffer.size(); }

    // add binary data to our package buffer.
    // name is required for properly checking is data is unpacked correctly.
    template<meh::constraint::is_packageable T>
    void pack(std::string name, T& data) {
        bool silent = _flags & PACK_SILENT;
        bool verbose = silent ? false : _flags & PACK_VERBOSE;
        if (_flags & PACK_DEBUG) {
            if (verbose) meh::Global::__log("writing in DEBUG mode");
            meh::write_buff(_buffer, name, true);
            if (verbose) meh::Global::__log("NAME written (" + name + ")");
        }
        meh::write_buff(_buffer, data);
        if (verbose) meh::Global::__log("DATA written");
        if (!silent) meh::Global::__log("data packed!");
    }

};


} // namespace meh