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

namespace meh::info {

// the version we are using for writing our files
// when the major version changes that means that 
// compatibility with files created in the previous file version
// might be inconsistent or broken.
// we keep track of this version so we can keep compatibility to read
// from older versions and report versioning errors correctly.
static constexpr const char* FILE_VERSION     = "v0.1_r1";

// unrelated from the file version, this is simply the version of our library.
// compatibility with older files should never be lost at a change of only the 
// library version
static constexpr const char* LIBR_VERSION     = "alpha_v0.1_r1";

}