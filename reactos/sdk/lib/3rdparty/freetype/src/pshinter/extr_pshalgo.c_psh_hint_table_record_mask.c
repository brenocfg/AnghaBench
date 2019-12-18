#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num_bits; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_1__* PS_Mask ;
typedef  int /*<<< orphan*/  PSH_Hint_Table ;
typedef  scalar_t__ FT_UInt ;
typedef  int FT_Int ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  psh_hint_table_record (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
  psh_hint_table_record_mask( PSH_Hint_Table  table,
                              PS_Mask         hint_mask )
  {
    FT_Int    mask = 0, val = 0;
    FT_Byte*  cursor = hint_mask->bytes;
    FT_UInt   idx, limit;


    limit = hint_mask->num_bits;

    for ( idx = 0; idx < limit; idx++ )
    {
      if ( mask == 0 )
      {
        val  = *cursor++;
        mask = 0x80;
      }

      if ( val & mask )
        psh_hint_table_record( table, idx );

      mask >>= 1;
    }
  }