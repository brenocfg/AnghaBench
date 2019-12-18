#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct input_stats {TYPE_2__ input_bitrate; TYPE_1__ demux_bitrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct input_stats*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void input_stats_Destroy(struct input_stats *stats)
{
    vlc_mutex_destroy(&stats->demux_bitrate.lock);
    vlc_mutex_destroy(&stats->input_bitrate.lock);
    free(stats);
}