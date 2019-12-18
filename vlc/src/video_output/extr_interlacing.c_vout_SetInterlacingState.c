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
struct TYPE_9__ {TYPE_2__* p; } ;
typedef  TYPE_3__ vout_thread_t ;
struct TYPE_7__ {int is_interlaced; scalar_t__ date; } ;
struct TYPE_8__ {TYPE_1__ interlacing; } ;

/* Variables and functions */
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  var_SetBool (TYPE_3__*,char*,int) ; 
 scalar_t__ vlc_tick_now () ; 

void vout_SetInterlacingState(vout_thread_t *vout, bool is_interlaced)
{
     /* Wait 30s before quiting interlacing mode */
    const int interlacing_change = (!!is_interlaced)
                                 - (!!vout->p->interlacing.is_interlaced);
    if (interlacing_change == 1 ||
        (interlacing_change == -1 &&
        vout->p->interlacing.date + VLC_TICK_FROM_SEC(30) < vlc_tick_now()))
    {
        msg_Dbg(vout, "Detected %s video",
                 is_interlaced ? "interlaced" : "progressive");
        var_SetBool(vout, "deinterlace-needed", is_interlaced);
        vout->p->interlacing.is_interlaced = is_interlaced;
    }
    if (is_interlaced)
        vout->p->interlacing.date = vlc_tick_now();
}