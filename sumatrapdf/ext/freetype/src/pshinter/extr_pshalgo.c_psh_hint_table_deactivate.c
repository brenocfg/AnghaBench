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
struct TYPE_6__ {int order; } ;
struct TYPE_5__ {scalar_t__ max_hints; TYPE_2__* hints; } ;
typedef  TYPE_1__* PSH_Hint_Table ;
typedef  TYPE_2__* PSH_Hint ;
typedef  scalar_t__ FT_UInt ;

/* Variables and functions */
 int /*<<< orphan*/  psh_hint_deactivate (TYPE_2__*) ; 

__attribute__((used)) static void
  psh_hint_table_deactivate( PSH_Hint_Table  table )
  {
    FT_UInt   count = table->max_hints;
    PSH_Hint  hint  = table->hints;


    for ( ; count > 0; count--, hint++ )
    {
      psh_hint_deactivate( hint );
      hint->order = -1;
    }
  }