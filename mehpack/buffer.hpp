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
#include "global.hpp"
#include "type.hpp"
#include "version.hpp"

// !!! IMPORTANT !!!
// the packaging layout as of FILE_VERSION_MAJOR <= 1 is:
//      with debug:
//      [NAME LENGTH][NAME STRING][TYPE][DATA]
//      without debug:
//      [TYPE][DATA]

#include <vector>

namespace meh {

// our main kind of storage, a simple buffer of bytes
using BinaryBuffer  = std::vector<meh::Byte>;

// here we define our basic packageable type packing implementation

#if __MEH_INTERNAL_FVER_MAJ <= 1    // writing behaviour for file version 1 and under

// packaging for basic types
template<meh::constraint::is_basic_packageable T>
inline void write_buff(meh::BinaryBuffer& buff, const T& data, meh::PackFlags flags, bool strip_type = false) {
    
}

#endif

}