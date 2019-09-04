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
struct TYPE_4__ {int /*<<< orphan*/  counters; } ;
typedef  TYPE_1__* PS_Dimension ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ps_dimension_end_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_mask_table_merge_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ps_dimension_end( PS_Dimension  dim,
                    FT_UInt       end_point,
                    FT_Memory     memory )
  {
    /* end hint mask table */
    ps_dimension_end_mask( dim, end_point );

    /* merge all counter masks into independent "paths" */
    return ps_mask_table_merge_all( &dim->counters, memory );
  }