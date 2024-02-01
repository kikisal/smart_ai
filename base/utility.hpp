#pragma once

#include <inttypes.h>

namespace utility
{
    template<typename R, typename ListLike>
    
    // gets any ListLike object that acts like a list, and returns the product of all of its elements
    R indexed_product(ListLike const& entries, size_t start) {
        auto size = entries.elements();
        R result = 0;

        if (start >= size || start < 0)
            return result;

        result = entries[start];
        for (int i = start + 1; i < size; ++i)
            result *= entries[i];
        
        return result;
    }
} // namespace utility
