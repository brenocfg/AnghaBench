#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* p; } ;
typedef  TYPE_3__ vout_thread_t ;
struct TYPE_10__ {scalar_t__ date; TYPE_5__* current; TYPE_5__* next; } ;
struct TYPE_9__ {int is_on; } ;
struct TYPE_12__ {TYPE_2__ displayed; int /*<<< orphan*/  rate; int /*<<< orphan*/  clock; int /*<<< orphan*/  render; TYPE_1__ pause; } ;
typedef  TYPE_4__ vout_thread_sys_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_13__ {scalar_t__ b_force; int /*<<< orphan*/  date; } ;

/* Variables and functions */
 scalar_t__ const INT64_MAX ; 
 scalar_t__ ThreadDisplayPreparePicture (TYPE_3__*,int,int,int*) ; 
 int ThreadDisplayRenderPicture (TYPE_3__*,int) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ VOUT_MWAIT_TOLERANCE ; 
 scalar_t__ const VOUT_REDISPLAY_DELAY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (TYPE_5__*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_clock_ConvertToSystem (int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 
 scalar_t__ vout_chrono_GetHigh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ThreadDisplayPicture(vout_thread_t *vout, vlc_tick_t *deadline)
{
    vout_thread_sys_t *sys = vout->p;
    bool frame_by_frame = !deadline;
    bool paused = sys->pause.is_on;
    bool first = !sys->displayed.current;

    assert(sys->clock);

    if (first)
        if (ThreadDisplayPreparePicture(vout, true, frame_by_frame, &paused)) /* FIXME not sure it is ok */
            return VLC_EGENERIC;

    if (!paused || frame_by_frame)
        while (!sys->displayed.next
            && !ThreadDisplayPreparePicture(vout, false, frame_by_frame, &paused))
            ;

    const vlc_tick_t system_now = vlc_tick_now();
    const vlc_tick_t render_delay = vout_chrono_GetHigh(&sys->render) + VOUT_MWAIT_TOLERANCE;

    bool drop_next_frame = frame_by_frame;
    vlc_tick_t date_next = VLC_TICK_INVALID;

    if (!paused && sys->displayed.next) {
        const vlc_tick_t next_system_pts =
            vlc_clock_ConvertToSystem(sys->clock, system_now,
                                      sys->displayed.next->date, sys->rate);
        if (unlikely(next_system_pts == INT64_MAX))
        {
            /* The clock was just paused, don't display the next frame (keep
             * the current one). */
            paused = true;
        }
        {
            date_next = next_system_pts - render_delay;
            if (date_next <= system_now)
                drop_next_frame = true;
        }
    }

    /* FIXME/XXX we must redisplay the last decoded picture (because
     * of potential vout updated, or filters update or SPU update)
     * For now a high update period is needed but it could be removed
     * if and only if:
     * - vout module emits events from theselves.
     * - *and* SPU is modified to emit an event or a deadline when needed.
     *
     * So it will be done later.
     */
    bool refresh = false;

    vlc_tick_t date_refresh = VLC_TICK_INVALID;
    if (sys->displayed.date != VLC_TICK_INVALID) {
        date_refresh = sys->displayed.date + VOUT_REDISPLAY_DELAY - render_delay;
        refresh = date_refresh <= system_now;
    }
    bool force_refresh = !drop_next_frame && refresh;

    if (!frame_by_frame) {
        if (date_refresh != VLC_TICK_INVALID)
            *deadline = date_refresh;
        if (date_next != VLC_TICK_INVALID && date_next < *deadline)
            *deadline = date_next;
    }

    if (!first && !refresh && !drop_next_frame) {
        return VLC_EGENERIC;
    }

    if (drop_next_frame) {
        picture_Release(sys->displayed.current);
        sys->displayed.current = sys->displayed.next;
        sys->displayed.next    = NULL;
    }

    if (!sys->displayed.current)
        return VLC_EGENERIC;

    /* display the picture immediately */
    bool is_forced = frame_by_frame || force_refresh || sys->displayed.current->b_force;
    int ret = ThreadDisplayRenderPicture(vout, is_forced);
    return force_refresh ? VLC_EGENERIC : ret;
}