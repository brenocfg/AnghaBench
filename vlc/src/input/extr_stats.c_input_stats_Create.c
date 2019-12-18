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
struct input_stats {int /*<<< orphan*/  lost_pictures; int /*<<< orphan*/  displayed_pictures; int /*<<< orphan*/  lost_abuffers; int /*<<< orphan*/  played_abuffers; int /*<<< orphan*/  decoded_video; int /*<<< orphan*/  decoded_audio; int /*<<< orphan*/  demux_discontinuity; int /*<<< orphan*/  demux_corrupted; int /*<<< orphan*/  demux_bitrate; int /*<<< orphan*/  input_bitrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_rate_Init (int /*<<< orphan*/ *) ; 
 struct input_stats* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct input_stats *input_stats_Create(void)
{
    struct input_stats *stats = malloc(sizeof (*stats));
    if (unlikely(stats == NULL))
        return NULL;

    input_rate_Init(&stats->input_bitrate);
    input_rate_Init(&stats->demux_bitrate);
    atomic_init(&stats->demux_corrupted, 0);
    atomic_init(&stats->demux_discontinuity, 0);
    atomic_init(&stats->decoded_audio, 0);
    atomic_init(&stats->decoded_video, 0);
    atomic_init(&stats->played_abuffers, 0);
    atomic_init(&stats->lost_abuffers, 0);
    atomic_init(&stats->displayed_pictures, 0);
    atomic_init(&stats->lost_pictures, 0);
    return stats;
}