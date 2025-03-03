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
#include "type_defs.hpp"

#include <bitset>
#include <print>

// !!! IMPORTANT !!!
// the packaging layout as of v0.1_r1 is:
//      with debug:
//      [NAME LENGTH][NAME STRING][TYPE][DATA]
//      without debug:
//      [TYPE][DATA]

namespace meh {



class Package {
private:
    using __Flags = std::bitset<1>;
    __Flags _flags;
    meh::BinaryBuffer _buffer;
    meh::Byte* _point = 0x00;

public:
    Package() {

    }

    meh::Byte* get_data() { return _buffer.data(); }
    size_t get_size() { return _buffer.size(); }

    template<meh::constraint::is_basic_packageable T>
    void pack(std::string name, T& data) {
        if (1) {
            uint16 name_len = static_cast<uint16>(name.size());
            meh::NumType num = meh::type_to_num<T>();
            _buffer.reserve(_buffer.size() + sizeof(name_len) + name.size() + sizeof(meh::NumType) + sizeof(T));

            _buffer.insert(
                _buffer.end(), 
                reinterpret_cast<meh::Byte*>(&name_len),
                reinterpret_cast<meh::Byte*>(&name_len) + sizeof(name_len));
            _buffer.insert(
                _buffer.end(), 
                name.begin(),
                name.end());
            _buffer.insert(
                _buffer.end(), 
                reinterpret_cast<meh::Byte*>(&num),
                reinterpret_cast<meh::Byte*>(&num) + sizeof(num));
            _buffer.insert(
                _buffer.end(), 
                reinterpret_cast<meh::Byte*>(&data),
                reinterpret_cast<meh::Byte*>(&data) + sizeof(T));
        }
    }


};

} // namespace meh