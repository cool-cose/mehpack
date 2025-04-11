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
#include "version.hpp"

namespace meh {

static constexpr Byte DEBUG_BYTE            = 0xDB;     // sof byte for buffers with debug symbols
static constexpr Byte RELEASE_BYTE          = 0xAA;     // sof byte for buffers without debug symbols

class Package {
private:
    PackFlags _flags = std::numeric_limits<PackFlags>::min();
    meh::BinaryBuffer _buffer;

    void __write_metadata() {
        if (_flags & PACK_DEBUG)
            _buffer.emplace_back(DEBUG_BYTE);
        else _buffer.emplace_back(RELEASE_BYTE);
        meh::write_buff(_buffer, meh::info::FILE_VERSION_MAJOR, true);
        meh::write_buff(_buffer, meh::info::FILE_VERSION_MINOR, true);
    }

public:
    Package() { __write_metadata(); }
    Package(uint8 flags) : _flags(flags) { __write_metadata(); }

    meh::Byte* data() { return _buffer.data(); }
    size_t size() { return _buffer.size(); }

    // add binary data to our package buffer.
    // name is required for properly checking is data is unpacked correctly.
    template<meh::constraint::is_packageable T>
    void pack(const std::string& name, T& data) {
        bool silent = _flags & PACK_SILENT;
        bool verbose = silent ? false : _flags & PACK_VERBOSE;
        if (_flags & PACK_DEBUG) {
        if (!silent) MEH_LOG("writing data -> " + name);
            if (verbose) {
                MEH_LOG("writing in DEBUG mode");
                MEH_LOG("writing NAME chunk");
                meh::write_buff_verbose(_buffer, name, true);
            }
            else {
                meh::write_buff(_buffer, name, true);
            }
        }
        else if (verbose) MEH_LOG("writing in RELEASE mode");
        if (verbose) {
            MEH_LOG("writing DATA chunk");
            meh::write_buff_verbose(_buffer, data);
        }
        else {
            meh::write_buff(_buffer, data);
        }
        if (!silent) MEH_LOG("DATA packed!");
    }

};

} // namespace meh