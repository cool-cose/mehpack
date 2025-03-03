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

// here we store data we might need globally, most importantly we 
// store the callbacks to the user defined log function

#include <format>
#include <functional>

namespace meh {

using LogCallback = std::function<void(std::string)>;

class Global {
private:
    friend class Package;

    inline static LogCallback _log_callback = [](std::string m){ printf("meh [log] -> %s", m.c_str()); };
    static void __log(std::string m) { _log_callback(std::format("mehpack >> {}", m)); }

    inline static LogCallback _err_callback = [](std::string m){ printf("meh [error] -> %s", m.c_str()); };
    static void __err(std::string m) { _log_callback(std::format("mehpack >> {}", m)); }

public:
    // set the function callback to log, your function must be able to accept a singular std::string argument.
    // DEFAULTS TO printf()
    static void set_logging_callback(const LogCallback& callback) { _log_callback = callback; }

    // set the function callback to log errors, your function must be able to accept a singular std::string argument.
    // DEFAULTS TO printf()
    static void set_error_callback(const LogCallback& callback) { _err_callback = callback; }
};

} // namespace meh