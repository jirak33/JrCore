#ifndef _JIRAK_CORE_TICK_UTILS_H
#define _JIRAK_CORE_TICK_UTILS_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"

#include <cstdio>
#include <string>

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     @namespace JrStringUtil
     JrStringUtil namespace.
     */
    namespace JrStringUtil {
    /**
     @defgroup jr_string_util string related.
     */
    //@{

        template<typename T>
        std::string toStringArrayObject(const std::string& name, T a[], size_t count)
        {
            std::string s;

            s.append("%s = { ", name.c_str());
            for (size_t i = 0; i < count; i++) {
                char buf[32];
                if (i > 0) {
                    ::sprintf(buf, ", ");
                    s.append(buf);
                }
                ::sprintf(buf, "%d", a[i]);
	            s.append(buf);
            }
            s.append(" }");

            return s;
        }

    //@}
    }   // end of JrStringUtil

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_TICK_UTILS_H


// <EOF>


