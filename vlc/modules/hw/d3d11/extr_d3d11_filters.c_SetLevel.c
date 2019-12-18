#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float Maximum; float Default; float Minimum; } ;
struct filter_level {float default_val; float max; float min; TYPE_1__ Range; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,float) ; 

__attribute__((used)) static void SetLevel(struct filter_level *range, float val)
{
    int level;
    if (val > range->default_val)
        level = (range->Range.Maximum - range->Range.Default) * (val - range->default_val) /
                (range->max - range->default_val);
    else if (val < range->default_val)
        level = (range->Range.Minimum - range->Range.Default) * (val - range->default_val) /
                (range->min - range->default_val);
    else
        level = 0;

    atomic_store( &range->level, range->Range.Default + level );
}