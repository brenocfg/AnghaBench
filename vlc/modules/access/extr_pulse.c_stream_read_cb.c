#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ pa_usec_t ;
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_7__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {size_t framesize; int discontinuity; int /*<<< orphan*/ * es; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_9__ {unsigned int i_nb_samples; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 TYPE_3__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  pa_stream_drop (int /*<<< orphan*/ *) ; 
 scalar_t__ pa_stream_get_latency (int /*<<< orphan*/ *,scalar_t__*,int*) ; 
 scalar_t__ pa_stream_peek (int /*<<< orphan*/ *,void const**,size_t*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_pa_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void stream_read_cb(pa_stream *s, size_t length, void *userdata)
{
    demux_t *demux = userdata;
    demux_sys_t *sys = demux->p_sys;
    const void *ptr;
    unsigned samples = length / sys->framesize;

    if (pa_stream_peek(s, &ptr, &length) < 0) {
        vlc_pa_error(demux, "cannot peek stream", sys->context);
        return;
    }

    vlc_tick_t pts = vlc_tick_now();
    pa_usec_t latency;
    int negative;

    if (pa_stream_get_latency(s, &latency, &negative) < 0) {
        vlc_pa_error(demux, "cannot determine latency", sys->context);
        return;
    }
    if (negative)
        pts += latency;
    else
        pts -= latency;

    es_out_SetPCR(demux->out, pts);
    if (unlikely(sys->es == NULL))
        goto race;

    block_t *block = block_Alloc(length);
    if (likely(block != NULL)) {
        memcpy(block->p_buffer, ptr, length);
        block->i_nb_samples = samples;
        block->i_dts = block->i_pts = pts;
        if (sys->discontinuity) {
            block->i_flags |= BLOCK_FLAG_DISCONTINUITY;
            sys->discontinuity = false;
        }

        es_out_Send(demux->out, sys->es, block);
    } else
        sys->discontinuity = true;
race:
    pa_stream_drop(s);
}