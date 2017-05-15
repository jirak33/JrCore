#ifndef _JIRAK_CORE_BASE_STACK_H
#define _JIRAK_CORE_BASE_STACK_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"

#include <cassert>
#include <cstring>

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     @class JrStack
     @brief stack data class.

     general stack data class.
     */

    template<class T>
    class JrStack {
    public:
	    JrStack(const uint32 COUNT)
		    : _items(0)
		    , _index(0)
		    , _maxIndexValue(0)
	    {
		    _items = new T[COUNT];
		    ::memset(_items, 0, sizeof(T) * COUNT); 
	    }

	    ~JrStack()
	    {
		    if (_items) {
			    delete[] _items;
			    _items = 0;
		    }
	    }

	    void init()
	    {
		    _index = 0;
		    _maxIndexValue = 0;
	    }

	    bool isEmpty() const { return (0 >= _index); }
	    size_t maxIndexValue() const { return _maxIndexValue; }

	    void push(T val)
	    {
		    _items[_index] = val;
		    _index++;
		    if (_maxIndexValue < _index) {
			    _maxIndexValue = _index;
		    }
	    }

	    T pop()
	    {
		    assert(1 <= _index);

		    T r = _items[_index - 1];
		    _index--;

		    return r;
	    }

        void clear()
        {
            while (!isEmpty()) {
                pop();
            }
        }

    private:
	    T* _items;
	    size_t _index;
	    size_t _maxIndexValue;
    };

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_BASE_STACK_H


// <EOF>


