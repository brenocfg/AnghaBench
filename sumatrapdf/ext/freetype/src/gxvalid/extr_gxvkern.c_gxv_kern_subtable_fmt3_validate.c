#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ subtable_length; TYPE_1__* face; } ;
struct TYPE_5__ {scalar_t__ num_glyphs; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  scalar_t__ FT_UShort ;
typedef  scalar_t__ FT_ULong ;
typedef  scalar_t__ FT_Bytes ;
typedef  scalar_t__ FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_INVALID_GLYPH_ID ; 
 int /*<<< orphan*/  FT_INVALID_OFFSET ; 
 scalar_t__ FT_NEXT_BYTE (scalar_t__) ; 
 scalar_t__ FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 scalar_t__ GXV_KERN_SUBTABLE_HEADER_SIZE ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_SET_ERR_IF_PARANOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_array_getlimits_byte (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,TYPE_2__*) ; 

__attribute__((used)) static void
  gxv_kern_subtable_fmt3_validate( FT_Bytes       table,
                                   FT_Bytes       limit,
                                   GXV_Validator  gxvalid )
  {
    FT_Bytes   p = table + GXV_KERN_SUBTABLE_HEADER_SIZE;
    FT_UShort  glyphCount;
    FT_Byte    kernValueCount;
    FT_Byte    leftClassCount;
    FT_Byte    rightClassCount;
    FT_Byte    flags;


    GXV_NAME_ENTER( "kern subtable format 3" );

    GXV_LIMIT_CHECK( 2 + 1 + 1 + 1 + 1 );
    glyphCount      = FT_NEXT_USHORT( p );
    kernValueCount  = FT_NEXT_BYTE( p );
    leftClassCount  = FT_NEXT_BYTE( p );
    rightClassCount = FT_NEXT_BYTE( p );
    flags           = FT_NEXT_BYTE( p );

    if ( gxvalid->face->num_glyphs != glyphCount )
    {
      GXV_TRACE(( "maxGID=%d, but glyphCount=%d\n",
                  gxvalid->face->num_glyphs, glyphCount ));
      GXV_SET_ERR_IF_PARANOID( FT_INVALID_GLYPH_ID );
    }

    if ( flags != 0 )
      GXV_TRACE(( "kern subtable fmt3 has nonzero value"
                  " (%d) in unused flag\n", flags ));
    /*
     * just skip kernValue[kernValueCount]
     */
    GXV_LIMIT_CHECK( 2 * kernValueCount );
    p += 2 * kernValueCount;

    /*
     * check leftClass[gid] < leftClassCount
     */
    {
      FT_Byte  min, max;


      GXV_LIMIT_CHECK( glyphCount );
      gxv_array_getlimits_byte( p, p + glyphCount, &min, &max, gxvalid );
      p += gxvalid->subtable_length;

      if ( leftClassCount < max )
        FT_INVALID_DATA;
    }

    /*
     * check rightClass[gid] < rightClassCount
     */
    {
      FT_Byte  min, max;


      GXV_LIMIT_CHECK( glyphCount );
      gxv_array_getlimits_byte( p, p + glyphCount, &min, &max, gxvalid );
      p += gxvalid->subtable_length;

      if ( rightClassCount < max )
        FT_INVALID_DATA;
    }

    /*
     * check kernIndex[i, j] < kernValueCount
     */
    {
      FT_UShort  i, j;


      for ( i = 0; i < leftClassCount; i++ )
      {
        for ( j = 0; j < rightClassCount; j++ )
        {
          GXV_LIMIT_CHECK( 1 );
          if ( kernValueCount < FT_NEXT_BYTE( p ) )
            FT_INVALID_OFFSET;
        }
      }
    }

    gxvalid->subtable_length = (FT_ULong)( p - table );

    GXV_EXIT;
  }