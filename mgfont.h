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
    char* name;
} MgFont;

typedef struct {
    UInt8* bitmap;
    Int32 width;
    Int32 height;
    Int32 dx;
    Int32 dy;
    Int32 sx;
    Int32 sy;
} MgFontCharacter;

MgFontLibrary* MgFontLibrary_create(void);
void MgFontLibrary_destroy(MgFontLibrary* library);

MgFont* MgFont_create(MgFontLibrary* library, void* data, Int32 dataSize);
void MgFont_destroy(MgFont* font);
MgError MgFont_setSize(MgFont* font, Int32 size);
char* MgFont_getName(MgFont* font);
Int32 MgFont_canDisplay(MgFont* font, Int32 utfCode);

MgFontCharacter* MgFontCharacter_create(MgFont* font, Int32 utfCode);
void MgFontCharacter_destroy(MgFontCharacter* character);
Int32 MgFontCharacter_getBitmapWidth(MgFontCharacter* character);
Int32 MgFontCharacter_getBitmapHeight(MgFontCharacter* character);
Int32 MgFontCharacter_getDeltaX(MgFontCharacter* character);
Int32 MgFontCharacter_getDeltaY(MgFontCharacter* character);
Int32 MgFontCharacter_getSizeX(MgFontCharacter* character);
Int32 MgFontCharacter_getSizeY(MgFontCharacter* character);
Int32 MgFontCharacter_read(MgFontCharacter* character, Int32 x, Int32 y);

#endif
