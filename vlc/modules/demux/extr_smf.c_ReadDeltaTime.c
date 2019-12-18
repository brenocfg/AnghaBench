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
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ offset; scalar_t__ length; int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ mtrk_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ReadVarInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ReadDeltaTime (stream_t *s, mtrk_t *track)
{
    int32_t delta_time;

    assert (vlc_stream_Tell (s) == track->start + track->offset);

    if (track->offset >= track->length)
    {
        /* This track is done */
        track->next = UINT64_MAX;
        return 0;
    }

    delta_time = ReadVarInt (s);
    if (delta_time < 0)
        return -1;

    track->next += delta_time;
    track->offset = vlc_stream_Tell (s) - track->start;
    return 0;
}