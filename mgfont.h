#ifndef MGFONT_H
#define MGFONT_H

#include <ft2build.h>
#include <freetype/freetype.h>
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

MgFontLibrary* MgFontLibrary_create();
void MgFontLibrary_destroy(MgFontLibrary* library);

MgFont* MgFont_create(MgFontLibrary* library, void* data, Int32 dataSize);
void MgFont_destroy(MgFont* font);
MgError MgFont_setSize(MgFont* font, Int32 size);

MgFontCharacter* MgFontCharacter_create(MgFont* font, UInt32 utfCode);
void MgFontCharacter_destroy(MgFontCharacter* character);

#endif
