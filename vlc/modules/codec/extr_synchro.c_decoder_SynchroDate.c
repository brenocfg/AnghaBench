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
struct TYPE_3__ {int /*<<< orphan*/  current_pts; } ;
typedef  TYPE_1__ decoder_synchro_t ;

/* Variables and functions */

vlc_tick_t decoder_SynchroDate( decoder_synchro_t * p_synchro )
{
    /* No need to lock, since PTS are only used by the video parser. */
    return p_synchro->current_pts;
}