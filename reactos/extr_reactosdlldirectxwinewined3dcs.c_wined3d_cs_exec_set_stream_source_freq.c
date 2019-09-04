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
struct wined3d_stream_state {int /*<<< orphan*/  flags; int /*<<< orphan*/  frequency; } ;
struct wined3d_cs_set_stream_source_freq {size_t stream_idx; int /*<<< orphan*/  flags; int /*<<< orphan*/  frequency; } ;
struct TYPE_2__ {struct wined3d_stream_state* streams; } ;
struct wined3d_cs {int /*<<< orphan*/  device; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_STREAMSRC ; 
 int /*<<< orphan*/  device_invalidate_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_set_stream_source_freq(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_stream_source_freq *op = data;
    struct wined3d_stream_state *stream;

    stream = &cs->state.streams[op->stream_idx];
    stream->frequency = op->frequency;
    stream->flags = op->flags;

    device_invalidate_state(cs->device, STATE_STREAMSRC);
}