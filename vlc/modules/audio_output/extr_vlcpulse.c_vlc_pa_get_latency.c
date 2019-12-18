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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ pa_usec_t ;
struct TYPE_3__ {scalar_t__ write_index; scalar_t__ write_index_corrupt; } ;
typedef  TYPE_1__ pa_timing_info ;
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  pa_sample_spec ;
typedef  int /*<<< orphan*/  pa_context ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ PA_ERR_NODATA ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pa_bytes_to_usec (scalar_t__,int /*<<< orphan*/  const*) ; 
 scalar_t__ pa_context_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pa_stream_get_sample_spec (int /*<<< orphan*/ *) ; 
 scalar_t__ pa_stream_get_time (int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_1__* pa_stream_get_timing_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_pa_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

vlc_tick_t vlc_pa_get_latency(vlc_object_t *obj, pa_context *ctx, pa_stream *s)
{
    /* NOTE: pa_stream_get_latency() will report 0 rather than negative latency
     * when the write index of a playback stream is behind its read index.
     * playback streams. So use the lower-level pa_stream_get_timing_info()
     * directly to obtain the correct write index and convert it to a time,
     * and compute the correct latency value by subtracting the stream (read)
     * time.
     *
     * On the read side, pa_stream_get_time() is used instead of
     * pa_stream_get_timing_info() for the sake of interpolation. */
    const pa_sample_spec *ss = pa_stream_get_sample_spec(s);
    const pa_timing_info *ti = pa_stream_get_timing_info(s);

    if (ti == NULL) {
        msg_Dbg(obj, "no timing infos");
        return VLC_TICK_INVALID;
    }

    if (ti->write_index_corrupt) {
        msg_Dbg(obj, "write index corrupt");
        return VLC_TICK_INVALID;
    }

    pa_usec_t wt = pa_bytes_to_usec((uint64_t)ti->write_index, ss);
    pa_usec_t rt;

    if (pa_stream_get_time(s, &rt)) {
        if (pa_context_errno(ctx) != PA_ERR_NODATA)
            vlc_pa_error(obj, "unknown time", ctx);
        return VLC_TICK_INVALID;
    }

    union { uint64_t u; int64_t s; } d;
    d.u = wt - rt;
    return d.s; /* non-overflowing unsigned to signed conversion */
}