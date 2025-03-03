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
#include "type.hpp"

#include <vector>

namespace meh {

// our main kind of storage, a simple buffer of bytes
using BinaryBuffer  = std::vector<meh::Byte>;

template<meh::constraint::is_basic_packageable T>
inline void write_buff(BinaryBuffer& buff, T& item) {
    size_t total_size = sizeof(meh::NumType) + sizeof(T);
    buff.reserve(total_size);

    meh::NumType num = meh::type_to_num<T>();
    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&item), reinterpret_cast<meh::Byte*>(&item) + sizeof(T));
}

inline void write_buff(BinaryBuffer& buff, const std::string& item, bool strip_type = false) {
    uint16 str_len = item.size();

    size_t total_size = strip_type ? sizeof(uint16) + str_len : sizeof(meh::NumType) + sizeof(uint16) + str_len;
    buff.reserve(total_size);

    if (!strip_type) {
        meh::NumType num = meh::NumType::STRING;
        buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));
    }

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&str_len), reinterpret_cast<meh::Byte*>(&str_len) + sizeof(str_len));
    buff.insert(buff.end(), item.begin(), item.end());
}

inline void write_buff(BinaryBuffer& buff, const char* item) {
    uint16 str_len = std::strlen(item);

    size_t total_size = sizeof(meh::NumType) + sizeof(uint16) + str_len;
    buff.reserve(total_size);

    meh::NumType num = meh::NumType::STRING;
    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&str_len), reinterpret_cast<meh::Byte*>(&str_len) + sizeof(str_len));
    buff.insert(buff.end(), item, item + str_len);
}

}