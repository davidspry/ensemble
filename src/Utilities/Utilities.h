//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>

namespace Utilities
{

template <typename T>
[[nodiscard]] inline static const T boundBy(T minimum, T maximum, T value) noexcept
{
    return std::max(minimum, std::min(maximum, value));
}

}

#endif
