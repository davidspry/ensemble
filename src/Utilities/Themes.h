//  Ensemble
//  Created by David Spry on 24/12/20.

#ifndef THEMES_H
#define THEMES_H

#include "UIColourScheme.h"

namespace Themes
{
/// @brief A light theme with a yellow accent colour.

static UIColourScheme light00 =
{
    {195},
    {15},
    {55},
    {246, 160, 77},
    {15}
};

/// @brief A dark theme with a yellow accent colour.

static UIColourScheme dark00 =
{
    {25},
    {235},
    {125},
    {246, 160, 77},
    {235}
};

/// @brief The active colour scheme.

static UIColourScheme & theme = dark00;
};

#endif
