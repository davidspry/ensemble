//  Ensemble
//  Created by David Spry on 22/12/20.

#ifndef UIFONTLIBRARY_H
#define UIFONTLIBRARY_H

#include "ofMain.h"

/// @brief A static library of `ofTrueTypeFont` font files.

class UIFontLibrary
{
public:
    UIFontLibrary();

public:
    /// @brief Get a pointer to the font at the given filepath in the given point size.
    /// @param filepath The filepath of the desired TrueTypeFont font file.
    /// @param pointSize The desired point size of the font.

    static ofTrueTypeFont * get(const char * filepath, int pointSize) noexcept(false);

    using FontLibrary = std::unordered_map<std::string, ofTrueTypeFont>;
    
private:
    /// @brief Load the font at the given filepath with the given point size and add it to the font library.
    /// @param filepath The filepath of the desired TrueTypeFont font file.
    /// @param pointSize The desired point size of the font.

    static ofTrueTypeFont * add(const char * filepath, int pointSize) noexcept(false);

    /// @brief Indicate whether the library contains the font located at the given path with the given point size.
    /// @param filepath The filepath of the TrueTypeFont font file.
    /// @param pointSize The point size of the font.

    static bool contains(const char * filepath, int pointSize);

private:
    static FontLibrary fonts;
};

#endif
