#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ num_glyphs; } ;
struct TYPE_17__ {int horiBearingY; scalar_t__ horiBearingX; void* horiAdvance; void* height; void* width; } ;
struct TYPE_16__ {TYPE_5__* font; } ;
struct TYPE_11__ {int default_char; int version; int file_size; int pixel_height; int ascent; } ;
struct TYPE_15__ {TYPE_1__ header; int /*<<< orphan*/ * fnt_frame; } ;
struct TYPE_14__ {int width; int rows; int pitch; scalar_t__ buffer; int /*<<< orphan*/  pixel_mode; } ;
struct TYPE_13__ {int bitmap_top; TYPE_2__* internal; int /*<<< orphan*/  face; TYPE_7__ metrics; int /*<<< orphan*/  format; scalar_t__ bitmap_left; TYPE_4__ bitmap; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
typedef  int FT_ULong ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Size ;
typedef  void* FT_Pos ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Int32 ;
typedef  TYPE_3__* FT_GlyphSlot ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  scalar_t__ FT_Bool ;
typedef  TYPE_4__ FT_Bitmap ;
typedef  TYPE_5__* FNT_Font ;
typedef  TYPE_6__* FNT_Face ;

/* Variables and functions */
 scalar_t__ FT_ALLOC_MULT (scalar_t__,int,int) ; 
 scalar_t__ FT_BOOL (int) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 TYPE_8__* FT_FACE (TYPE_6__*) ; 
 int /*<<< orphan*/  FT_FACE_MEMORY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_GLYPH_FORMAT_BITMAP ; 
 int /*<<< orphan*/  FT_GLYPH_OWN_BITMAP ; 
 int FT_LOAD_BITMAP_METRICS_ONLY ; 
 int FT_NEXT_ULONG_LE (int /*<<< orphan*/ *) ; 
 void* FT_NEXT_USHORT_LE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_PIXEL_MODE_MONO ; 
 int /*<<< orphan*/  FT_SIZE_FACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE1 (char*) ; 
 int /*<<< orphan*/  FT_TRACE2 (char*) ; 
 int /*<<< orphan*/  Invalid_Argument ; 
 int /*<<< orphan*/  Invalid_Face_Handle ; 
 int /*<<< orphan*/  Invalid_File_Format ; 
 int /*<<< orphan*/  ft_synthesize_vertical_metrics (TYPE_7__*,void*) ; 

__attribute__((used)) static FT_Error
  FNT_Load_Glyph( FT_GlyphSlot  slot,
                  FT_Size       size,
                  FT_UInt       glyph_index,
                  FT_Int32      load_flags )
  {
    FNT_Face    face   = (FNT_Face)FT_SIZE_FACE( size );
    FNT_Font    font;
    FT_Error    error  = FT_Err_Ok;
    FT_Byte*    p;
    FT_UInt     len;
    FT_Bitmap*  bitmap = &slot->bitmap;
    FT_ULong    offset;
    FT_Bool     new_format;


    if ( !face )
    {
      error = FT_THROW( Invalid_Face_Handle );
      goto Exit;
    }

    font = face->font;

    if ( !font                                                   ||
         glyph_index >= (FT_UInt)( FT_FACE( face )->num_glyphs ) )
    {
      error = FT_THROW( Invalid_Argument );
      goto Exit;
    }

    FT_TRACE1(( "FNT_Load_Glyph: glyph index %d\n", glyph_index ));

    if ( glyph_index > 0 )
      glyph_index--;                           /* revert to real index */
    else
      glyph_index = font->header.default_char; /* the `.notdef' glyph  */

    new_format = FT_BOOL( font->header.version == 0x300 );
    len        = new_format ? 6 : 4;

    /* get glyph width and offset */
    offset = ( new_format ? 148 : 118 ) + len * glyph_index;

    if ( offset >= font->header.file_size - 2 - ( new_format ? 4 : 2 ) )
    {
      FT_TRACE2(( "invalid FNT offset\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Exit;
    }

    p = font->fnt_frame + offset;

    bitmap->width = FT_NEXT_USHORT_LE( p );

    /* jump to glyph entry */
    if ( new_format )
      offset = FT_NEXT_ULONG_LE( p );
    else
      offset = FT_NEXT_USHORT_LE( p );

    if ( offset >= font->header.file_size )
    {
      FT_TRACE2(( "invalid FNT offset\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Exit;
    }

    bitmap->rows       = font->header.pixel_height;
    bitmap->pixel_mode = FT_PIXEL_MODE_MONO;

    slot->bitmap_left     = 0;
    slot->bitmap_top      = font->header.ascent;
    slot->format          = FT_GLYPH_FORMAT_BITMAP;

    /* now set up metrics */
    slot->metrics.width        = (FT_Pos)( bitmap->width << 6 );
    slot->metrics.height       = (FT_Pos)( bitmap->rows << 6 );
    slot->metrics.horiAdvance  = (FT_Pos)( bitmap->width << 6 );
    slot->metrics.horiBearingX = 0;
    slot->metrics.horiBearingY = slot->bitmap_top << 6;

    ft_synthesize_vertical_metrics( &slot->metrics,
                                    (FT_Pos)( bitmap->rows << 6 ) );

    if ( load_flags & FT_LOAD_BITMAP_METRICS_ONLY )
      goto Exit;

    /* jump to glyph data */
    p = font->fnt_frame + /* font->header.bits_offset */ + offset;

    /* allocate and build bitmap */
    {
      FT_Memory  memory = FT_FACE_MEMORY( slot->face );
      FT_UInt    pitch  = ( bitmap->width + 7 ) >> 3;
      FT_Byte*   column;
      FT_Byte*   write;


      bitmap->pitch = (int)pitch;
      if ( !pitch                                                 ||
           offset + pitch * bitmap->rows > font->header.file_size )
      {
        FT_TRACE2(( "invalid bitmap width\n" ));
        error = FT_THROW( Invalid_File_Format );
        goto Exit;
      }

      /* note: since glyphs are stored in columns and not in rows we */
      /*       can't use ft_glyphslot_set_bitmap                     */
      if ( FT_ALLOC_MULT( bitmap->buffer, bitmap->rows, pitch ) )
        goto Exit;

      column = (FT_Byte*)bitmap->buffer;

      for ( ; pitch > 0; pitch--, column++ )
      {
        FT_Byte*  limit = p + bitmap->rows;


        for ( write = column; p < limit; p++, write += bitmap->pitch )
          *write = *p;
      }

      slot->internal->flags = FT_GLYPH_OWN_BITMAP;
    }

  Exit:
    return error;
  }