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
struct deint_mode {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ VAProcFilterCapDeinterlacing ;

/* Variables and functions */

__attribute__((used)) static inline bool
OpenDeinterlace_IsValidType(filter_t * filter,
                            VAProcFilterCapDeinterlacing const caps[],
                            unsigned int num_caps,
                            struct deint_mode const * deint_mode)
{
    (void) filter;
    for (unsigned int j = 0; j < num_caps; ++j)
        if (caps[j].type == deint_mode->type)
            return true;
    return false;
}