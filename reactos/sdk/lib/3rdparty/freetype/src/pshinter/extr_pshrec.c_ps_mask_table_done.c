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
struct TYPE_3__ {scalar_t__ max_masks; scalar_t__ num_masks; int /*<<< orphan*/  masks; } ;
typedef  TYPE_1__* PS_Mask_Table ;
typedef  int /*<<< orphan*/  PS_Mask ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_mask_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  ps_mask_table_done( PS_Mask_Table  table,
                      FT_Memory      memory )
  {
    FT_UInt  count = table->max_masks;
    PS_Mask  mask  = table->masks;


    for ( ; count > 0; count--, mask++ )
      ps_mask_done( mask, memory );

    FT_FREE( table->masks );
    table->num_masks = 0;
    table->max_masks = 0;
  }