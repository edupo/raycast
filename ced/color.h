#pragma once

#include "types.h"

extern const CedColor color_black;
extern const CedColor color_white;
extern const CedColor color_purple;
extern const CedColor color_red;
extern const CedColor color_orange;
extern const CedColor color_brown;
extern const CedColor color_yellow;
extern const CedColor color_lime;
extern const CedColor color_green;
extern const CedColor color_dark_cyan;
extern const CedColor color_dark_blue;
extern const CedColor color_blue;
extern const CedColor color_light_blue;
extern const CedColor color_light_cyan;
extern const CedColor color_light_grey;
extern const CedColor color_grey;
extern const CedColor color_dark_grey;
extern const CedColor color_transparent;
extern const CedColor color_error;

int ced_color_eq(const CedColor a, const CedColor b);
CedColor ced_color_lerp(const CedColor a, const CedColor b, float value);