#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ nBlockAlign; } ;
typedef  TYPE_6__ WAVEFORMATEX ;
struct TYPE_15__ {int rtStreamStart; int /*<<< orphan*/ * pClock; } ;
struct TYPE_16__ {TYPE_4__ filter; TYPE_3__* pInputPin; } ;
struct TYPE_18__ {scalar_t__ last_playpos; int play_time; scalar_t__ buf_size; TYPE_5__ renderer; int /*<<< orphan*/  IReferenceClock_iface; } ;
struct TYPE_12__ {scalar_t__ pbFormat; } ;
struct TYPE_13__ {TYPE_1__ mtCurrent; } ;
struct TYPE_14__ {TYPE_2__ pin; } ;
typedef  int REFERENCE_TIME ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_7__ DSoundRenderImpl ;

/* Variables and functions */
 int /*<<< orphan*/  DSoundRender_UpdatePositions (TYPE_7__*,scalar_t__*,scalar_t__*) ; 
 int DSoundRenderer_Max_Fill ; 
 int /*<<< orphan*/  IReferenceClock_GetTime (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__,...) ; 
 scalar_t__ pos_from_time (TYPE_7__*,int) ; 
 int time_from_pos (TYPE_7__*,scalar_t__) ; 

__attribute__((used)) static HRESULT DSoundRender_GetWritePos(DSoundRenderImpl *This, DWORD *ret_writepos, REFERENCE_TIME write_at, DWORD *pfree, DWORD *skip)
{
    WAVEFORMATEX *wfx = (WAVEFORMATEX*)This->renderer.pInputPin->pin.mtCurrent.pbFormat;
    DWORD writepos, min_writepos, playpos;
    REFERENCE_TIME max_lag = 50 * 10000;
    REFERENCE_TIME min_lag = 25 * 10000;
    REFERENCE_TIME cur, writepos_t, delta_t;

    DSoundRender_UpdatePositions(This, &writepos, &min_writepos);
    playpos = This->last_playpos;
    if (This->renderer.filter.pClock == &This->IReferenceClock_iface) {
        max_lag = min_lag;
        cur = This->play_time + time_from_pos(This, playpos);
        cur -= This->renderer.filter.rtStreamStart;
    } else if (This->renderer.filter.pClock) {
        IReferenceClock_GetTime(This->renderer.filter.pClock, &cur);
        cur -= This->renderer.filter.rtStreamStart;
    } else
        write_at = -1;

    if (writepos == min_writepos)
        max_lag = 0;

    *skip = 0;
    if (write_at < 0) {
        *ret_writepos = writepos;
        goto end;
    }

    if (writepos >= playpos)
        writepos_t = cur + time_from_pos(This, writepos - playpos);
    else
        writepos_t = cur + time_from_pos(This, This->buf_size + writepos - playpos);

    /* write_at: Starting time of sample */
    /* cur: current time of play position */
    /* writepos_t: current time of our pointer play position */
    delta_t = write_at - writepos_t;
    if (delta_t >= -max_lag && delta_t <= max_lag) {
        TRACE("Continuing from old position\n");
        *ret_writepos = writepos;
    } else if (delta_t < 0) {
        REFERENCE_TIME past, min_writepos_t;
        WARN("Delta too big %i/%i, overwriting old data or even skipping\n", (int)delta_t / 10000, (int)max_lag / 10000);
        if (min_writepos >= playpos)
            min_writepos_t = cur + time_from_pos(This, min_writepos - playpos);
        else
            min_writepos_t = cur + time_from_pos(This, This->buf_size - playpos + min_writepos);
        past = min_writepos_t - write_at;
        if (past >= 0) {
            DWORD skipbytes = pos_from_time(This, past);
            WARN("Skipping %u bytes\n", skipbytes);
            *skip = skipbytes;
            *ret_writepos = min_writepos;
        } else {
            DWORD aheadbytes = pos_from_time(This, -past);
            WARN("Advancing %u bytes\n", aheadbytes);
            *ret_writepos = (min_writepos + aheadbytes) % This->buf_size;
        }
    } else /* delta_t > 0 */ {
        DWORD aheadbytes;
        WARN("Delta too big %i/%i, too far ahead\n", (int)delta_t / 10000, (int)max_lag / 10000);
        aheadbytes = pos_from_time(This, delta_t);
        WARN("Advancing %u bytes\n", aheadbytes);
        if (delta_t >= DSoundRenderer_Max_Fill)
            return S_FALSE;
        *ret_writepos = (min_writepos + aheadbytes) % This->buf_size;
    }
end:
    if (playpos > *ret_writepos)
        *pfree = playpos - *ret_writepos;
    else if (playpos == *ret_writepos)
        *pfree = This->buf_size - wfx->nBlockAlign;
    else
        *pfree = This->buf_size + playpos - *ret_writepos;
    if (time_from_pos(This, This->buf_size - *pfree) >= DSoundRenderer_Max_Fill) {
        TRACE("Blocked: too full %i / %i\n", (int)(time_from_pos(This, This->buf_size - *pfree)/10000), (int)(DSoundRenderer_Max_Fill / 10000));
        return S_FALSE;
    }
    return S_OK;
}