//
//  PlatformConfig.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  13/03/2017
//
//  --------------------------------------------------------------
//
//  Adapted from code I originally wrote for my game framework, Skyrocket.
//  Found here:
//  https://github.com/jacobmilligan/Skyrocket
//

#pragma once

namespace robo {

/// @brief Defines several OS-related macros and constants that can be used
/// for platform-specific code.
///
/// Both the target_platform and target_family
/// constants can and should be used for platform-detection over the predefines
/// macros to avoid horrible macro debugging problems that can crop up.
/// The macros should only be used to conditionally include headers or to
/// conditionally include blocks of code that otherwise wouldn't compile on
/// the current platform. Each OS-detection macro is a boolean value of either 1 or 0
/// @ingroup platform

/// @var target_platform
/// The operating system currently being compiled on
/// @var target_family
/// The family of operating systems currently being compiled on

/// @brief Defines the current operating system
enum class Platform {
    unknown,
    mac,
    windows,
    linux,
    ios,
    iphone_sim,
    android
};

/// @brief Defines the family of operating systems that the current platform
/// belongs to
enum class OSFamily {
    unknown,
    apple,
    microsoft,
    linux,
    android
};

/// @brief MacOSX operating system
#define ROBONAV_OS_MAC_OSX 0

/// @brief IOS operating system
#define ROBONAV_OS_IOS 0

/// @brief Android operating system
#define ROBONAV_OS_ANDROID 0

/// @brief Windows operating system
#define ROBONAV_OS_WINDOWS 0

/// @brief Linux operating systems
#define ROBONAV_OS_LINUX 0


#if defined(__APPLE__) && defined(__MACH__)
const auto target_family = OSFamily::apple;
    #include <TargetConditionals.h>
    
    #if TARGET_IPHONE_SIMULATOR == 1
#define ROBONAV_OS_IOS
        #define ROBONAV_OS_IOS 1
        const auto target_platform = Platform::iphone_sim;
    
    #elif TARGET_OS_IPHONE == 1
#undef ROBONAV_OS_IOS
        #define ROBONAV_OS_IOS 1
        const auto target_platform = Platform::ios;
    
    #elif TARGET_OS_MAC == 1
        #undef ROBONAV_OS_MAC_OSX
        #define ROBONAV_OS_MAC_OSX 1
const auto target_platform = Platform::mac;
    
    #endif
#elif defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN64) \
|| defined(_WIN32) || defined(_WINDOWS) || defined(__TOS_WIN__)
	#undef ROBONAV_OS_WINDOWS
    #define ROBONAV_OS_WINDOWS 1
    const auto target_family = OSFamily::microsoft;
    const auto target_platform = Platform::windows;

#elif defined(__linux__) || defined(__linux) || defined(linux)
    #undef ROBONAV_OS_LINUX
    #define ROBONAV_OS_LINUX 1
    const auto target_family = OSFamily::linux;
    const auto target_platform = Platform::linux;

#elif defined(__ANDROID__)
    #undef ROBONAV_OS_ANDROID
    #define ROBONAV_OS_ANDROID 1
    const auto target_family = OSFamily::android;
    const auto target_platform = Platform::android;
    const auto android_api_level = __ANDROID_API__;
    
#else
    const auto target_family = OSFamily::unknown;
    const auto target_platform = Platform::unknown;
#endif

////////////////////////
// Compiler detection //
////////////////////////

enum class Compiler {
    unknown,
    clang,
    gcc,
    msvc
};

#define ROBONAV_COMPILER_CLANG 0
#define ROBONAV_COMPILER_GCC 0
#define ROBONAV_COMPILER_MSVC 0

#if defined(__clang__)
    #undef ROBONAV_COMPILER_CLANG
    #define ROBONAV_COMPILER_CLANG 1
const auto target_compiler = Compiler::clang;
#elif defined(__GNUC__)
#undef ROBONAV_COMPILER_GCC
    #define ROBONAV_COMPILER_GCC 1
    const auto target_compiler = Compiler::gcc;
#elif defined(_MSC_VER)
    #undef ROBONAV_COMPILER_MSVC
    #define ROBONAV_COMPILER_MSVC 1
    const auto target_compiler = Compiler::msvc;
#else
    const auto target_compiler = Compiler::unknown;
#endif

//////////////////////////////
// Compiler implementations //
//////////////////////////////

#define ROBONAV_STRINGIFY(x) #x

#if ROBONAV_COMPILER_CLANG == 1
    #define ROBONAV_PUSH_WARNING _Pragma("clang diagnostic push")
    #define ROBONAV_IGNORE_WARNING(x) _Pragma( ROBONAV_STRINGIFY(clang diagnostic ignored #x) )
    #define ROBONAV_POP_WARNING _Pragma("clang diagnostic pop")
    #define ROBONAV_PACKED(n) __attribute__((packed, aligned(n)))
    #define ROBONAV_FUNCTION_NAME __PRETTY_FUNCTION__
#elif ROBONAV_COMPILER_GCC == 1
    #define ROBONAV_PUSH_WARNING _Pragma( ROBONAV_STRINGIFY(GCC diagnostic push)
    #define ROBONAV_IGNORE_WARNING(x) _Pragma( ROBONAV_STRINGIFY(GCC diagnostic ignored #x)
    #define ROBONAV_POP_WARNING _Pragma( ROBONAV_STRINGIFY(GCC diagnostic pop)
    #define ROBONAV_PACKED(n) __attribute__((packed, aligned(n)))
	#define ROBONAV_FUNCTION_NAME __PRETTY_FUNCTION__
#elif ROBONAV_COMPILER_MSVC == 1
    #define ROBONAV_PUSH_WARNING _Pragma( ROBONAV_STRINGIFY(warning( push ))
    #define ROBONAV_IGNORE_WARNING(x) _Pragma( ROBONAV_STRINGIFY(warning( disable: #x ))
    #define ROBONAV_POP_WARNING _Pragma( ROBONAV_STRINGIFY(warning( pop ))
	#define ROBONAV_FUNCTION_NAME __FUNCTION__
#endif



}
