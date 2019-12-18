#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_14__ {int /*<<< orphan*/  lock; } ;
struct TYPE_16__ {TYPE_1__ bdj; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_17__ {int cmd; int plane; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_4__ BD_OVERLAY ;

/* Variables and functions */
#define  BD_OVERLAY_CLEAR 133 
#define  BD_OVERLAY_CLOSE 132 
#define  BD_OVERLAY_DRAW 131 
#define  BD_OVERLAY_FLUSH 130 
#define  BD_OVERLAY_INIT 129 
#define  BD_OVERLAY_WIPE 128 
 int MAX_OVERLAY ; 
 int /*<<< orphan*/  blurayActivateOverlay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  blurayClearOverlay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  blurayCloseOverlay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  blurayDrawOverlay (TYPE_2__*,TYPE_4__ const* const) ; 
 int /*<<< orphan*/  blurayInitOverlay (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayOverlayProc(void *ptr, const BD_OVERLAY *const overlay)
{
    demux_t *p_demux = (demux_t*)ptr;
    demux_sys_t *p_sys = p_demux->p_sys;

    vlc_mutex_lock(&p_sys->bdj.lock);

    if (!overlay) {
        msg_Info(p_demux, "Closing overlays.");
        for (int i = 0; i < MAX_OVERLAY; i++)
            blurayCloseOverlay(p_demux, i);
        vlc_mutex_unlock(&p_sys->bdj.lock);
        return;
    }

    switch (overlay->cmd) {
    case BD_OVERLAY_INIT:
        msg_Info(p_demux, "Initializing overlay");
        blurayInitOverlay(p_demux, overlay->plane, overlay->w, overlay->h);
        break;
    case BD_OVERLAY_CLOSE:
        blurayClearOverlay(p_demux, overlay->plane);
        blurayCloseOverlay(p_demux, overlay->plane);
        break;
    case BD_OVERLAY_CLEAR:
        blurayClearOverlay(p_demux, overlay->plane);
        break;
    case BD_OVERLAY_FLUSH:
        blurayActivateOverlay(p_demux, overlay->plane);
        break;
    case BD_OVERLAY_DRAW:
    case BD_OVERLAY_WIPE:
        blurayDrawOverlay(p_demux, overlay);
        break;
    default:
        msg_Warn(p_demux, "Unknown BD overlay command: %u", overlay->cmd);
        break;
    }

    vlc_mutex_unlock(&p_sys->bdj.lock);
}