#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int glyph_count; } ;
typedef  TYPE_1__* OTV_Validator ;
typedef  int FT_UInt ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int DeviceTableOffset ; 
 int /*<<< orphan*/  FT_INVALID_GLYPH_ID ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  otv_Device_validate (int,TYPE_1__*) ; 

__attribute__((used)) static void
  otv_GlyphAssembly_validate( FT_Bytes       table,
                              OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   pcnt, table_size;
    FT_UInt   i;

    OTV_OPTIONAL_TABLE( DeviceTableOffset );


    /* OTV_NAME_ENTER( "GlyphAssembly" ); */

    OTV_LIMIT_CHECK( 6 );

    p += 2;                           /* Skip the Italics Correction value */
    OTV_OPTIONAL_OFFSET( DeviceTableOffset );
    pcnt = FT_NEXT_USHORT( p );

    OTV_LIMIT_CHECK( 8 * pcnt );
    table_size = 6 + 8 * pcnt;

    OTV_SIZE_CHECK( DeviceTableOffset );
    if ( DeviceTableOffset )
      otv_Device_validate( table + DeviceTableOffset, otvalid );

    for ( i = 0; i < pcnt; i++ )
    {
      FT_UInt  gid;


      gid = FT_NEXT_USHORT( p );
      if ( gid >= otvalid->glyph_count )
        FT_INVALID_GLYPH_ID;
      p += 2*4;             /* skip the Start, End, Full, and Flags fields */
    }

    /* OTV_EXIT; */
  }