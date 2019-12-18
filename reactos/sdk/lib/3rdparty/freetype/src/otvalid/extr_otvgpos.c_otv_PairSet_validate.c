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
struct TYPE_4__ {int extra3; } ;
typedef  TYPE_1__* OTV_Validator ;
typedef  int FT_UInt ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int /*<<< orphan*/  otv_ValueRecord_validate (int,int,TYPE_1__*) ; 
 int otv_value_length (int) ; 

__attribute__((used)) static void
  otv_PairSet_validate( FT_Bytes       table,
                        FT_UInt        format1,
                        FT_UInt        format2,
                        OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   value_len1, value_len2, PairValueCount;


    OTV_NAME_ENTER( "PairSet" );

    otvalid->extra3 = table;

    OTV_LIMIT_CHECK( 2 );
    PairValueCount = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (PairValueCount = %d)\n", PairValueCount ));

    value_len1 = otv_value_length( format1 );
    value_len2 = otv_value_length( format2 );

    OTV_LIMIT_CHECK( PairValueCount * ( value_len1 + value_len2 + 2 ) );

    /* PairValueRecord */
    for ( ; PairValueCount > 0; PairValueCount-- )
    {
      p += 2;       /* skip SecondGlyph */

      if ( format1 )
        otv_ValueRecord_validate( p, format1, otvalid ); /* Value1 */
      p += value_len1;

      if ( format2 )
        otv_ValueRecord_validate( p, format2, otvalid ); /* Value2 */
      p += value_len2;
    }

    OTV_EXIT;
  }