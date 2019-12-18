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
struct TYPE_3__ {int /*<<< orphan*/  hints; int /*<<< orphan*/  masks; int /*<<< orphan*/  counters; } ;
typedef  TYPE_1__* PS_Dimension ;
typedef  int /*<<< orphan*/  FT_Memory ;

/* Variables and functions */
 int /*<<< orphan*/  ps_hint_table_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_mask_table_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  ps_dimension_done( PS_Dimension  dimension,
                     FT_Memory     memory )
  {
    ps_mask_table_done( &dimension->counters, memory );
    ps_mask_table_done( &dimension->masks,    memory );
    ps_hint_table_done( &dimension->hints,    memory );
  }