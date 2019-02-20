#include "mgfont.h"
#include "mgmemory.h"

/// source: https://www.freetype.org/freetype2/docs/tutorial

// limits required for safe integer multiplication
#define MAX_BITMAP_WIDTH 40000
#define MAX_BITMAP_HEIGHT 40000

MgFontLibrary* MgFontLibrary_create(void)
{
    MgFontLibrary* library = MgMemory_allocate(sizeof(MgFontLibrary));
    if(library == NULL) return NULL;
    
    FT_Error error = FT_Init_FreeType(&(library->ft_library));
    if(error)
    {
        MgMemory_free(library);
        return NULL;
    }
    
    return library;
}

void MgFontLibrary_destroy(MgFontLibrary* library)
{
    if(library == NULL) return;
    FT_Done_FreeType(library->ft_library);
    MgMemory_free(library);
}


MgFont* MgFont_create(MgFontLibrary* library, void* data, Int32 dataSize)
{
    if(data == NULL || dataSize < 1) return NULL;
    
    MgFont* font = MgMemory_allocate(sizeof(MgFont));
    if(font == NULL) return NULL;
    
    FT_Error error = FT_New_Memory_Face(library->ft_library, data, dataSize, 0, &(font->ft_face));
    if(error)
    {
        MgMemory_free(font);
        return NULL;
    }
    
    if((font->ft_face->face_flags & FT_FACE_FLAG_SCALABLE) == 0)
    {
        MgFont_destroy(font);
        return NULL;
    }

    font->name = font->ft_face->family_name;
    
    return font;
}

void MgFont_destroy(MgFont* font)
{
    if(font == NULL) return;
    FT_Done_Face(font->ft_face);
    MgMemory_free(font);
}

MgError MgFont_setSize(MgFont* font, Int32 size)
{
    if(font == NULL) return -1;
    if(size < 0) return -1;
    if(size > MAX_BITMAP_HEIGHT) return -1;
    FT_Error error = FT_Set_Pixel_Sizes(font->ft_face, 0, (UInt32)size);
    if(error) return -1;
    else return 0;
}

char* MgFont_getName(MgFont* font)
{
    return font->name;
}

Int32 MgFont_canDisplay(MgFont *font, Int32 utfCode)
{
    return FT_Get_Char_Index(font->ft_face, (UInt32)utfCode) != 0;
}

MgFontCharacter* MgFontCharacter_create(MgFont* font, Int32 utfCode)
{
    if(font == NULL) return NULL;
    
    MgFontCharacter* character = MgMemory_allocate(sizeof(MgFontCharacter));
    if(character == NULL) return NULL;
    
    UInt32 index = FT_Get_Char_Index(font->ft_face, (UInt32)utfCode);
    FT_Error error = FT_Load_Glyph(font->ft_face, index, 0);
    if(error)
    {
        MgMemory_free(character);
        return NULL;
    }
    
    error = FT_Render_Glyph(font->ft_face->glyph, FT_RENDER_MODE_NORMAL);
    if(error)
    {
        MgMemory_free(character);
        return NULL;
    }
    
    character->dx = font->ft_face->glyph->bitmap_left;
    character->dy = -font->ft_face->glyph->bitmap_top;
    character->sx = (Int32)font->ft_face->glyph->metrics.width;
    character->sy = (Int32)font->ft_face->glyph->metrics.height;
    character->width = (Int32)(font->ft_face->glyph->bitmap.width);
    character->height = (Int32)(font->ft_face->glyph->bitmap.rows);
    
    if(character->width > MAX_BITMAP_WIDTH || character->height > MAX_BITMAP_HEIGHT)
    {
        MgMemory_free(character);
        return NULL;
    }
    
    Int32 pixelCount = character->width * character->height;
    character->bitmap = MgMemory_allocate((UInt32)pixelCount*sizeof(UInt8));
    if(character->bitmap == NULL)
    {
        MgMemory_free(character);
        return NULL;
    }
    
    for(int y = 0; y < character->height; y++)
    {
        for(int x = 0; x < character->width; x++)
        {
            int i = x + y*character->width;
            character->bitmap[i] = font->ft_face->glyph->bitmap.buffer[i];
        }
    }

    return character;
}

void MgFontCharacter_destroy(MgFontCharacter* character)
{
    if(character == NULL) return;
    MgMemory_free(character->bitmap);
    MgMemory_free(character);
}

Int32 MgFontCharacter_getBitmapWidth(MgFontCharacter* character)
{
    return character->width;
}

Int32 MgFontCharacter_getBitmapHeight(MgFontCharacter* character)
{
    return character->height;
}

Int32 MgFontCharacter_getDeltaX(MgFontCharacter* character)
{
    return character->dx;
}

Int32 MgFontCharacter_getDeltaY(MgFontCharacter* character)
{
    return character->dy;
}

Int32 MgFontCharacter_getSizeX(MgFontCharacter* character)
{
    return character->sx;
}

Int32 MgFontCharacter_getSizeY(MgFontCharacter* character)
{
    return character->sy;
}

Int32 MgFontCharacter_read(MgFontCharacter* character, Int32 x, Int32 y)
{
    if(x < 0) return 0;
    if(x >= character->width) return 0;
    if(y < 0) return 0;
    if(y >= character->height) return 0;
    Int32 i = x + y*character->width;
    return (Int32)(character->bitmap[i]);
}
