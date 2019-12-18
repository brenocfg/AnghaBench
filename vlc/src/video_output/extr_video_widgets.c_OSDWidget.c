#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_9__ {TYPE_3__* p_sys; int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  pf_update; int /*<<< orphan*/  pf_validate; } ;
typedef  TYPE_1__ subpicture_updater_t ;
struct TYPE_10__ {int i_channel; int b_ephemer; int b_absolute; int b_fade; scalar_t__ i_start; scalar_t__ i_stop; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_11__ {int type; int position; } ;
typedef  TYPE_3__ osdwidget_spu_updater_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSDWidgetDestroy ; 
 int /*<<< orphan*/  OSDWidgetUpdate ; 
 int /*<<< orphan*/  OSDWidgetValidate ; 
 int OSD_HOR_SLIDER ; 
 int OSD_VERT_SLIDER ; 
 int VLC_CLIP (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 TYPE_2__* subpicture_New (TYPE_1__*) ; 
 int /*<<< orphan*/  var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_tick_now () ; 
 int /*<<< orphan*/  vout_PutSubpicture (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void OSDWidget(vout_thread_t *vout, int channel, int type, int position)
{
    if (!var_InheritBool(vout, "osd"))
        return;
    if (type == OSD_HOR_SLIDER || type == OSD_VERT_SLIDER)
        position = VLC_CLIP(position, 0, 100);

    osdwidget_spu_updater_sys_t *sys = malloc(sizeof(*sys));
    if (!sys)
        return;
    sys->type     = type;
    sys->position = position;

    subpicture_updater_t updater = {
        .pf_validate = OSDWidgetValidate,
        .pf_update   = OSDWidgetUpdate,
        .pf_destroy  = OSDWidgetDestroy,
        .p_sys       = sys,
    };
    subpicture_t *subpic = subpicture_New(&updater);
    if (!subpic) {
        free(sys);
        return;
    }

    subpic->i_channel  = channel;
    subpic->i_start    = vlc_tick_now();
    subpic->i_stop     = subpic->i_start + VLC_TICK_FROM_MS(1200);
    subpic->b_ephemer  = true;
    subpic->b_absolute = true;
    subpic->b_fade     = true;

    vout_PutSubpicture(vout, subpic);
}