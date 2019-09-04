#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num_masks; } ;
struct TYPE_7__ {scalar_t__ num_masks; } ;
struct TYPE_6__ {scalar_t__ num_hints; } ;
struct TYPE_9__ {TYPE_3__ counters; TYPE_2__ masks; TYPE_1__ hints; } ;
typedef  TYPE_4__* PS_Dimension ;

/* Variables and functions */

__attribute__((used)) static void
  ps_dimension_init( PS_Dimension  dimension )
  {
    dimension->hints.num_hints    = 0;
    dimension->masks.num_masks    = 0;
    dimension->counters.num_masks = 0;
  }