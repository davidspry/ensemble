//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>

namespace Utilities
{

/// @brief Bound the given value by the given range.
/// @param minimum The minimum value of the desired range.
/// @param maximum The maximum value of the desired range.
/// @param value The input value to be bounded.

template <typename T>
[[nodiscard]] inline static const T boundBy(T minimum, T maximum, T value) noexcept
{
    return std::max(minimum, std::min(maximum, value));
}

/// @brief Count the number of lines in the given string.
/// @param text The string whose number of lines should be counted.

[[nodiscard]] inline static const int numberOfLines(const std::string & text) noexcept
{
    return 1 + static_cast<int>(std::count(text.begin(), text.end(), '\n'));
}

}

#endif
