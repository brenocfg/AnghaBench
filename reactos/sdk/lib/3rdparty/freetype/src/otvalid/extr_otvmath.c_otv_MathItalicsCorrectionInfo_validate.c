#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OTV_Validator ;
typedef  int FT_UInt ;
typedef  scalar_t__ FT_Int ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int Coverage ; 
 int DeviceTableOffset ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  FT_UNUSED (scalar_t__) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  otv_Coverage_validate (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  otv_Device_validate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_MathItalicsCorrectionInfo_validate( FT_Bytes       table,
                                          OTV_Validator  otvalid,
                                          FT_Int         isItalic )
  {
    FT_Bytes  p = table;
    FT_UInt   i, cnt, table_size;

    OTV_OPTIONAL_TABLE( Coverage );
    OTV_OPTIONAL_TABLE( DeviceTableOffset );

    FT_UNUSED( isItalic );  /* only used if tracing is active */


    OTV_NAME_ENTER( isItalic ? "MathItalicsCorrectionInfo"
                             : "MathTopAccentAttachment" );

    OTV_LIMIT_CHECK( 4 );

    OTV_OPTIONAL_OFFSET( Coverage );
    cnt = FT_NEXT_USHORT( p );

    OTV_LIMIT_CHECK( 4 * cnt );
    table_size = 4 + 4 * cnt;

    OTV_SIZE_CHECK( Coverage );
    otv_Coverage_validate( table + Coverage, otvalid, (FT_Int)cnt );

    for ( i = 0; i < cnt; i++ )
    {
      p += 2;                                            /* Skip the value */
      OTV_OPTIONAL_OFFSET( DeviceTableOffset );
      OTV_SIZE_CHECK( DeviceTableOffset );
      if ( DeviceTableOffset )
        otv_Device_validate( table + DeviceTableOffset, otvalid );
    }

    OTV_EXIT;
  }