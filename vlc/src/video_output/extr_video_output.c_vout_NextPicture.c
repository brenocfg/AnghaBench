#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* p; } ;
typedef  TYPE_4__ vout_thread_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_8__ {scalar_t__ last; scalar_t__ timestamp; } ;
struct TYPE_7__ {scalar_t__ timestamp; } ;
struct TYPE_9__ {int display; int /*<<< orphan*/  control; TYPE_2__ step; TYPE_1__ displayed; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 scalar_t__ ThreadDisplayPicture (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vout_control_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_control_Release (int /*<<< orphan*/ *) ; 

void vout_NextPicture(vout_thread_t *vout, vlc_tick_t *duration)
{
    assert(!vout->p->dummy);
    assert(vout->p->display);
    *duration = 0;

    vout_control_Hold(&vout->p->control);
    if (vout->p->step.last == VLC_TICK_INVALID)
        vout->p->step.last = vout->p->displayed.timestamp;

    if (ThreadDisplayPicture(vout, NULL) == 0) {
        vout->p->step.timestamp = vout->p->displayed.timestamp;

        if (vout->p->step.last != VLC_TICK_INVALID &&
            vout->p->step.timestamp > vout->p->step.last) {
            *duration = vout->p->step.timestamp - vout->p->step.last;
            vout->p->step.last = vout->p->step.timestamp;
            /* TODO advance subpicture by the duration ... */
        }
    }
    vout_control_Release(&vout->p->control);
}