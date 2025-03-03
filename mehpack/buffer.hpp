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

#include <vector>

namespace meh {

// our main kind of storage, a simple buffer of bytes
using BinaryBuffer  = std::vector<meh::Byte>;

// here we define our basic packageable type packing implementation

// write a basic type to buffer (excluding strings)
#if __MEH_INTERNAL_FVER_MAJ <= 1    // writing behaviour for file version 1 and under

template<meh::constraint::is_basic_packageable T>
inline void write_buff(BinaryBuffer& buff, const T& item, bool strip_type = false) {
    size_t total_size = strip_type ? sizeof(T) : sizeof(meh::NumType) + sizeof(T);
    buff.reserve(buff.size() + total_size);

    if (!strip_type) {
        meh::NumType num = meh::type_to_num<T>();
        buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));
    }

    buff.insert(buff.end(), reinterpret_cast<const meh::Byte*>(&item), reinterpret_cast<const meh::Byte*>(&item) + sizeof(T));
}
template<meh::constraint::is_basic_packageable T>
inline void write_buff_verbose(BinaryBuffer& buff, const T& item, bool strip_type = false) {
    size_t total_size = strip_type ? sizeof(T) : sizeof(meh::NumType) + sizeof(T);
    buff.reserve(buff.size() + total_size);
    MEH_LOG("reserved in BYTE BUFFER -> " + std::to_string(total_size) + "BYTES // of total size SIZE -> " + std::to_string(buff.size() + total_size));

    if (!strip_type) {
        meh::NumType num = meh::type_to_num<T>();
        buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));
        MEH_LOG("write metadata for TYPE -> " + meh::numtype_to_str(num));
    }
    else MEH_LOG("metadata for TYPE is STRIPPED");

    buff.insert(buff.end(), reinterpret_cast<const meh::Byte*>(&item), reinterpret_cast<const meh::Byte*>(&item) + sizeof(T));
    MEH_LOG("write DATA body -> " + std::to_string(sizeof(item)) + " BYTES");
}

// specialization for writing std::strings, which are our chosen string in the library.
// set strip_type to true to strip type info (usually useful when we are writing names and we know its going to be a string already)
inline void write_buff(BinaryBuffer& buff, const std::string& item, bool strip_type = false) {
    uint16 str_len = item.size();

    size_t total_size = strip_type ? sizeof(uint16) + str_len : sizeof(meh::NumType) + sizeof(uint16) + str_len;
    buff.reserve(buff.size() + total_size);

    if (!strip_type) {
        meh::NumType num = meh::NumType::STRING;
        buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));
    }

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&str_len), reinterpret_cast<meh::Byte*>(&str_len) + sizeof(str_len));
    buff.insert(buff.end(), item.begin(), item.end());
}
inline void write_buff_verbose(BinaryBuffer& buff, const std::string& item, bool strip_type = false) {
    uint16 str_len = item.size();

    size_t total_size = strip_type ? sizeof(uint16) + str_len : sizeof(meh::NumType) + sizeof(uint16) + str_len;
    buff.reserve(buff.size() + total_size);
    MEH_LOG("reserved in BYTE BUFFER -> " + std::to_string(total_size) + " BYTES // of total size SIZE -> " + std::to_string(buff.size() + total_size));

    if (!strip_type) {
        meh::NumType num = meh::NumType::STRING;
        buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));
        MEH_LOG("write metadata for TYPE -> " + meh::numtype_to_str(num));
    }
    else MEH_LOG("metadata for TYPE is STRIPPED");

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&str_len), reinterpret_cast<meh::Byte*>(&str_len) + sizeof(str_len));
    MEH_LOG("write DATA length -> " + std::to_string(str_len));
    buff.insert(buff.end(), item.begin(), item.end());
    MEH_LOG("write DATA body");
}

// specialization for const char*, honestly it's here just for the peace of mind, we dont use const char* in the 
// library but it's here just in case
inline void write_buff(BinaryBuffer& buff, const char* item) {
    uint16 str_len = std::char_traits<char>::length(item);

    size_t total_size = sizeof(meh::NumType) + sizeof(uint16) + str_len;
    buff.reserve(buff.size() + total_size);

    meh::NumType num = meh::NumType::STRING;
    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&str_len), reinterpret_cast<meh::Byte*>(&str_len) + sizeof(str_len));
    buff.insert(buff.end(), item, item + str_len);
}
inline void write_buff_verbose(BinaryBuffer& buff, const char* item) {
    uint16 str_len = std::char_traits<char>::length(item);
    
    size_t total_size = sizeof(meh::NumType) + sizeof(uint16) + str_len;
    buff.reserve(buff.size() + total_size);
    MEH_LOG("reserved in BYTE BUFFER -> " + std::to_string(total_size) + " BYTES // of total size SIZE -> " + std::to_string(buff.size() + total_size));

    meh::NumType num = meh::NumType::STRING;
    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&num), reinterpret_cast<meh::Byte*>(&num) + sizeof(meh::NumType));
    MEH_LOG("write metadata for TYPE -> " + meh::numtype_to_str(num));

    buff.insert(buff.end(), reinterpret_cast<meh::Byte*>(&str_len), reinterpret_cast<meh::Byte*>(&str_len) + sizeof(str_len));
    MEH_LOG("write DATA length -> " + std::to_string(str_len));
    buff.insert(buff.end(), item, item + str_len);
    MEH_LOG("write DATA body");
}

#endif

}