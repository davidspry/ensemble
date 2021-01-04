//  Ensemble
//  Created by David Spry on 4/1/21.

#ifndef UIFONT_H
#define UIFONT_H

#include "ofMain.h"
#include "UIFontLibrary.h"

/// @brief Constants defining the available UIFont types.

enum class UIFontType { BMP, TTF };

/// @brief An interface that wraps `ofTrueTypeFont` and `ofBitmapFont` together.

class UIFont
{
public:
    /// @brief Construct the default bitmap font.
    
    UIFont() noexcept
    {
        fontType = UIFontType::BMP;
        ttf = nullptr;
    }
    
    /// @brief Initialise the UIFont with the given true type font.
    /// @param filepath The filepath of the TTF font file, relative to Ensemble's 'data' folder.
    /// @param pointSize The desired point size of the font.

    UIFont(const char * filepath, int pointSize) noexcept(false)
    {
        fontType = UIFontType::TTF;
        setTrueTypeFont(filepath, pointSize);
    }

public:
    /// @brief Use the default bitmap font with the given size.
    /// @param size The desired size of bitmap font.

    inline void setBitmapFont() noexcept
    {
        fontType = UIFontType::BMP;
    }
    
    /// @brief Use a true type font.
    /// @param filepath The filepath of the TTF font file, relative to Ensemble's 'data' folder.
    /// @param pointSize The desired point size of the font.
    /// @throw An exception will be thrown in the case where the given filepath cannot be loaded.

    inline void setTrueTypeFont(const char * filepath, int pointSize) noexcept(false)
    {
        fontType = UIFontType::TTF;
        
        ttf = UIFontLibrary::get(filepath, pointSize);
    }
    
    /// @brief Using the selected font, get the bounding box of the given string at the given position.
    /// @param string The string whose bounding box should be computed.
    /// @param x The x-coordinate of the desired text position.
    /// @param y The y-coordinate of the desired text position.

    inline const ofRectangle getStringBoundingBox(std::string string, int x = 0, int y = 0)
    {
        switch (fontType)
        {
            case UIFontType::TTF:
            {
                return ttf->getStringBoundingBox(string, x, y);
            }

            case UIFontType::BMP:
            {
                constexpr int dx = +1;
                constexpr int dy = -2;
                return ofBitmapFont().getBoundingBox(string, x + dx, y + dy);
            }
        }
    }

    /// @brief Use the selected font to draw the given string at the given position.
    /// @param string The string to be drawn.
    /// @param x The x-coordinate of the desired text position.
    /// @param y The y-coordinate of the desired text position.

    void drawString(std::string_view string, int x, int y) const noexcept
    {
        switch (fontType)
        {
            case UIFontType::TTF:
            {
                return drawStringTTF(string, x, y);
            }
                
            case UIFontType::BMP:
            {
                constexpr int dx = +1;
                constexpr int dy = -2;
                return drawStringBMP(string, x + dx, y + dy);
            }
        }
    }
    
private:
    /// @brief Draw the given string at the given location using the bitmap font.
    /// @param string The string to be drawn.
    /// @param x The x-coordinate of the text's position.
    /// @param y The y-coordinate of the text's position.

    void drawStringBMP(std::string_view string, int x, int y) const
    {
        ofDrawBitmapString(string, x, y);
    }
    
    /// @brief Draw the given string at the given location using the true type font.
    /// @param string The string to be drawn.
    /// @param x The x-coordinate of the text's position.
    /// @param y The y-coordinate of the text's position.
    
    void drawStringTTF(std::string_view string, int x, int y) const
    {
        if (ttf == nullptr)
        {
            ofLogError("UIFont", "TTF font is nullptr!");
            return;
        }
        
        ttf->drawString(std::string(string), x, y);
    }

private:
    UIFontType fontType;
    ofTrueTypeFont * ttf;
};

#endif
