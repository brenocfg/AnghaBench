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
struct TYPE_3__ {scalar_t__ max_hints; int /*<<< orphan*/  hints; } ;
typedef  TYPE_1__* PS_Hint_Table ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ FT_PAD_CEIL (scalar_t__,int) ; 
 int /*<<< orphan*/  FT_RENEW_ARRAY (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static FT_Error
  ps_hint_table_ensure( PS_Hint_Table  table,
                        FT_UInt        count,
                        FT_Memory      memory )
  {
    FT_UInt   old_max = table->max_hints;
    FT_UInt   new_max = count;
    FT_Error  error   = FT_Err_Ok;


    if ( new_max > old_max )
    {
      /* try to grow the table */
      new_max = FT_PAD_CEIL( new_max, 8 );
      if ( !FT_RENEW_ARRAY( table->hints, old_max, new_max ) )
        table->max_hints = new_max;
    }
    return error;
  }