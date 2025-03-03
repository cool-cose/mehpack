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

// since we do not support anything lower than C++20 we do a quick check for C++20

#if __cplusplus < 202002L
    #error "mehpack requires at least C++20"
#endif

// we hold versioning info as a static variable and simply just change it in the code 
// when a new version is out.
// versions are formatted as:
//      [OPTIONAL]state_v(VERSION)_r(REVISION)

#define __MEH_INTERNAL_FVER_MAJ     0x00
#define __MEH_INTERNAL_FVER_MIN     0x01

namespace meh::info {

// the version we are using for writing our files
// when the major version changes that means that 
// compatibility with files created in the previous file version
// might be inconsistent or broken.
// we keep track of this version so we can keep compatibility to read
// from older versions and report versioning errors correctly.
static constexpr signed char FILE_VERSION_MAJOR         = __MEH_INTERNAL_FVER_MAJ;
static constexpr signed char FILE_VERSION_MINOR         = __MEH_INTERNAL_FVER_MIN;

// unrelated from the file version, this is simply the version of our library.
// compatibility with older files should never be lost at a change of only the 
// library version
static constexpr const char* LIBR_VERSION     = "alpha_v0.1_r1";

}