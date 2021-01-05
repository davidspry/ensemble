//  Ensemble
//  Created by David Spry on 22/12/20.

#include "UIFontLibrary.h"

UIFontLibrary::UIFontLibrary()
{
    
}

ofTrueTypeFont * UIFontLibrary::get(const char * filepath, int pointSize) noexcept(false)
{
    if (UIFontLibrary::contains(filepath, pointSize))
    {
        const auto key = std::to_string(pointSize) + filepath;
        return &(UIFontLibrary::fonts[key]);
    }

    else
    {
        return UIFontLibrary::add(filepath, pointSize);
    }
}

bool UIFontLibrary::contains(const char * filepath, int pointSize)
{
    FontLibrary const * library = &UIFontLibrary::fonts;
    const auto target = library->find(std::to_string(pointSize) + filepath);
    const bool exists = target != library->end();

    return exists && target->second.getSize() == pointSize;
}

ofTrueTypeFont * UIFontLibrary::add(const char * filepath, int pointSize) noexcept(false)
{
    FontLibrary * const library = &UIFontLibrary::fonts;

    auto result = library->insert({std::to_string(pointSize) + filepath, {}});

    if (!result.second)
    {
        constexpr auto error = "The UIFontLibrary failed to add the requested font.";
        throw std::invalid_argument(error);
    }
    
    auto & font = result.first->second;
    
    if (!(font.load(filepath, pointSize)))
    {
        constexpr auto error = "The given filepath could not be loaded from successfully.";
        throw std::invalid_argument(error);
    }
    
    return &font;
}

UIFontLibrary::FontLibrary UIFontLibrary::fonts = {};
