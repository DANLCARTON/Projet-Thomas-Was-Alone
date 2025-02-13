#ifndef COLORS_HPP
#define COLORS_HPP

typedef struct Col3f {
    float r;
    float g;
    float b;
} ColorRGB;

ColorRGB createColor(float r, float g, float b);

ColorRGB addColors(ColorRGB c1, ColorRGB c2);
ColorRGB subColors(ColorRGB c1, ColorRGB c2);
ColorRGB multColors(ColorRGB c1, ColorRGB c2);

ColorRGB multColor(ColorRGB c, float a);
ColorRGB divColor(ColorRGB c, float a);

ColorRGB clampColor(ColorRGB c);

#endif