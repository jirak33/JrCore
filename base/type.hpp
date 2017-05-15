#ifndef _JIRAK_CORE_BASE_TYPE_H
#define _JIRAK_CORE_BASE_TYPE_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_WIN32)
#include <ctime>
#endif

#include <cstddef>
#include <limits>

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     @defgroup type_def standard types.
     @brief standard type define for jirak library.
     */
    //@{
    #ifndef _JIRAK_STANDARD_TYPES
    #define _JIRAK_STANDARD_TYPES
    ////////////////////////////////////////////////////////////////////////////
        typedef   signed char       int8;   ///< 8 bit signed int.
        typedef unsigned char      uint8;   ///< 8 bit unsigned int.
        typedef   signed short      int16;  ///< 16 bit signed int.
        typedef unsigned short     uint16;  ///< 16 bit unsigned int.
        typedef   signed int        int32;  ///< 32 bit signed int.
        typedef unsigned int       uint32;  ///< 32 bit unsigned int.
        #if defined(_WIN32)
            typedef   signed __int64    int64;  ///< 64 bit signed int.
            typedef unsigned __int64   uint64;  ///< 64 bit unsigned int.
        #else   // *nix
            typedef   signed long long  int64;  ///< 64 bit signed int.
            typedef unsigned long long uint64;  ///< 64 bit unsigned int.
        #endif
    ////////////////////////////////////////////////////////////////////////////
    #endif  // _JIRAK_STANDARD_TYPES

        typedef          float    float32;  ///< 32bit float type.
        typedef          double   float64;  ///< 64bit float type.

    #if defined(_WIN32)
        typedef      __time32_t  time_t32;  ///< 32bit time_t type.
        typedef      __time64_t  time_t64;  ///< 64bit time_t type.
    #else //< *nix
        typedef          int32   time_t32;  ///< 32bit time_t type.
        typedef          int64   time_t64;  ///< 64bit time_t type.
    #endif
    //@}

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_BASE_TYPE_H


// <EOF>


