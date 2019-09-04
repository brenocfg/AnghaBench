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
struct TYPE_4__ {int extra1; scalar_t__ extra2; } ;
typedef  TYPE_1__* OTV_Validator ;
typedef  int FT_UInt ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  OTV_ENTER ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (scalar_t__) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (scalar_t__) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 scalar_t__ anchor_offset ; 
 int /*<<< orphan*/  otv_Anchor_validate (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static void
  otv_x_sxy( FT_Bytes       table,
             OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   Count, count1, table_size;


    OTV_ENTER;

    OTV_LIMIT_CHECK( 2 );

    Count = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (Count = %d)\n", Count ));

    OTV_LIMIT_CHECK( Count * otvalid->extra1 * 2 );

    table_size = Count * otvalid->extra1 * 2 + 2;

    for ( ; Count > 0; Count-- )
      for ( count1 = otvalid->extra1; count1 > 0; count1-- )
      {
        OTV_OPTIONAL_TABLE( anchor_offset );


        OTV_OPTIONAL_OFFSET( anchor_offset );

        if ( otvalid->extra2 )
        {
          OTV_SIZE_CHECK( anchor_offset );
          if ( anchor_offset )
            otv_Anchor_validate( table + anchor_offset, otvalid );
        }
        else
          otv_Anchor_validate( table + anchor_offset, otvalid );
      }

    OTV_EXIT;
  }