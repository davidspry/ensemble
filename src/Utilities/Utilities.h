//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
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

/// @brief Construct a string with the given text and the given length by padding or truncating.
/// @param text The text to construct the string with.
/// @param length The desired number of characters to include.

[[nodiscard]] static std::string stringWithLength(const std::string & text, unsigned int length)
{
    std::string string;
    string.reserve(length);
    size_t const textSize = text.size();

    if (textSize > length)
    {
        string.insert(0, text, 0, length - 3);
        string.insert(length - 3, 3, '.');
    }

    else
    {
        string.insert(0, text);
        string.insert(textSize, length - textSize, ' ');
    }

    return string;
}

}

#endif
