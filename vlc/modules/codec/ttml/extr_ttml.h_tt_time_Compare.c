#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  tt_time_t ;

/* Variables and functions */
 scalar_t__ tt_time_Convert (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int tt_time_Compare( const tt_time_t *t1, const tt_time_t *t2 )
{
    vlc_tick_t ttt1 = tt_time_Convert( t1 );
    vlc_tick_t ttt2 = tt_time_Convert( t2 );
    if (ttt1 < ttt2)
        return -1;
    return ttt1 > ttt2;
}