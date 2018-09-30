#include "mgfont.h"
#include "mgmemory.h"

/// source: https://www.freetype.org/freetype2/docs/tutorial

// limits required for safe integer multiplication
#define MAX_BITMAP_WIDTH 40000
#define MAX_BITMAP_HEIGHT 40000

MgFontLibrary* mgFontLibrary_create()
{
    MgFontLibrary* library = mgMemory_allocate(sizeof(MgFontLibrary));
    if(library == NULL) return NULL;
    
    FT_Error error = FT_Init_FreeType(&(library->ft_library));
    if(error)
    {
        mgMemory_free(library);
        return NULL;
    }
    
    return library;
}

void mgFontLibrary_destroy(MgFontLibrary* library)
{
    if(library == NULL) return;
    FT_Done_FreeType(library->ft_library);
    mgMemory_free(library);
}


MgFont* mgFont_create(MgFontLibrary* library, void* data, Int32 dataSize)
{
    if(data == NULL || dataSize < 1) return NULL;
    
    MgFont* font = mgMemory_allocate(sizeof(MgFont));
    if(font == NULL) return NULL;
    
    FT_Error error = FT_New_Memory_Face(library->ft_library, data, dataSize, 0, &(font->ft_face));
    if(error)
    {
        mgMemory_free(font);
        return NULL;
    }
    
    if((font->ft_face->face_flags & FT_FACE_FLAG_SCALABLE) == 0)
    {
        mgFont_destroy(font);
        return NULL;
    }
    
    return font;
}

void mgFont_destroy(MgFont* font)
{
    if(font == NULL) return;
    FT_Done_Face(font->ft_face);
    mgMemory_free(font);
}

MgError mgFont_setSize(MgFont* font, Int32 size)
{
    if(font == NULL) return -1;
    if(size < 0) return -1;
    if(size > MAX_BITMAP_HEIGHT) return -1;
    FT_Error error = FT_Set_Pixel_Sizes(font->ft_face, 0, size);
    if(error) return -1;
    else return 0;
}


MgFontCharacter* mgFontCharacter_create(MgFont* font, UInt32 utfCode)
{
    if(font == NULL) return NULL;
    
    MgFontCharacter* character = mgMemory_allocate(sizeof(MgFontCharacter));
    if(character == NULL) return NULL;
    
    UInt32 index = FT_Get_Char_Index(font->ft_face, utfCode);
    FT_Error error = FT_Load_Glyph(font->ft_face, index, 0);
    if(error)
    {
        mgMemory_free(character);
        return NULL;
    }
    
    error = FT_Render_Glyph(font->ft_face->glyph, FT_RENDER_MODE_NORMAL);
    if(error)
    {
        mgMemory_free(character);
        return NULL;
    }
    
    character->dx = font->ft_face->glyph->bitmap_left;
    character->dy = -font->ft_face->glyph->bitmap_top;
    character->width = mgTypes_UInt32_to_Int32(font->ft_face->glyph->bitmap.width);
    character->height = mgTypes_UInt32_to_Int32(font->ft_face->glyph->bitmap.rows);
    
    if(character->width > MAX_BITMAP_WIDTH || character->height > MAX_BITMAP_HEIGHT)
    {
        mgMemory_free(character);
        return NULL;
    }
    
    Int32 pixelCount = character->width * character->height;
    character->bitmap = mgMemory_allocate(pixelCount*sizeof(UInt8));
    if(character->bitmap == NULL)
    {
        mgMemory_free(character);
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

void mgFontCharacter_destroy(MgFontCharacter* character)
{
    if(character == NULL) return;
    mgMemory_free(character->bitmap);
    mgMemory_free(character);
}