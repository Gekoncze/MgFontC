#ifndef MGFONT_H
#define MGFONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "mgtypes.h"

typedef struct {
    FT_Library ft_library;
} MgFontLibrary;

typedef struct {
    FT_Face ft_face;
} MgFont;

typedef struct {
    UInt8* bitmap;
    Int32 width;
    Int32 height;
    Int32 dx;
    Int32 dy;
} MgFontCharacter;

MgFontLibrary* mgFontLibrary_create();
void mgFontLibrary_destroy(MgFontLibrary* library);

MgFont* mgFont_create(MgFontLibrary* library, void* data, Int32 dataSize);
void mgFont_destroy(MgFont* font);
MgError mgFont_setSize(MgFont* font, Int32 size);

MgFontCharacter* mgFontCharacter_create(MgFont* font, UInt32 utfCode);
void mgFontCharacter_destroy(MgFontCharacter* character);

#endif