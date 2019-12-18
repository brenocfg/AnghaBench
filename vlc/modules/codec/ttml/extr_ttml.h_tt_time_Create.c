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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_3__ {scalar_t__ frames; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ tt_time_t ;

/* Variables and functions */

__attribute__((used)) static inline tt_time_t tt_time_Create( vlc_tick_t i )
{
    tt_time_t t;
    t.base = i;
    t.frames = 0;
    return t;
}