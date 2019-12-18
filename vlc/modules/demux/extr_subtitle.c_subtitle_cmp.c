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
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_2__ {scalar_t__ i_start; } ;
typedef  TYPE_1__ subtitle_t ;

/* Variables and functions */

__attribute__((used)) static int subtitle_cmp( const void *first, const void *second )
{
    vlc_tick_t result = ((subtitle_t *)(first))->i_start - ((subtitle_t *)(second))->i_start;
    /* Return -1, 0 ,1, and not directly subtraction
     * as result can be > INT_MAX */
    return result == 0 ? 0 : result > 0 ? 1 : -1;
}