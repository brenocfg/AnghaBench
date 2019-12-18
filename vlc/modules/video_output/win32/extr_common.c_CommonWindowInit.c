#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * hvideownd; int /*<<< orphan*/ * hparent; int /*<<< orphan*/  event; int /*<<< orphan*/  dxgidebug_dll; } ;
typedef  TYPE_3__ vout_display_sys_win32_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_17__ {int /*<<< orphan*/ * hvideownd; int /*<<< orphan*/ * hparent; } ;
typedef  TYPE_4__ event_hwnd_t ;
struct TYPE_18__ {int is_projected; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_5__ event_cfg_t ;
struct TYPE_14__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {TYPE_1__ display; int /*<<< orphan*/ * window; } ;
struct TYPE_19__ {TYPE_2__ vdcfg; } ;
typedef  TYPE_6__ display_win32_area_t ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int /*<<< orphan*/  CommonPlacePicture (int /*<<< orphan*/ *,TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  EventThreadCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EventThreadStart (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int CommonWindowInit(vlc_object_t *obj, display_win32_area_t *area,
                     vout_display_sys_win32_t *sys, bool projection_gestures)
{
    if (unlikely(area->vdcfg.window == NULL))
        return VLC_EGENERIC;

    /* */
#if !defined(NDEBUG) && defined(HAVE_DXGIDEBUG_H)
    sys->dxgidebug_dll = LoadLibrary(TEXT("DXGIDEBUG.DLL"));
#endif
    sys->hvideownd = NULL;
    sys->hparent   = NULL;

    /* */
    sys->event = EventThreadCreate(obj, area->vdcfg.window);
    if (!sys->event)
        return VLC_EGENERIC;

    /* */
    event_cfg_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.width  = area->vdcfg.display.width;
    cfg.height = area->vdcfg.display.height;
    cfg.is_projected = projection_gestures;

    event_hwnd_t hwnd;
    if (EventThreadStart(sys->event, &hwnd, &cfg))
        return VLC_EGENERIC;

    sys->hparent       = hwnd.hparent;
    sys->hvideownd     = hwnd.hvideownd;

    CommonPlacePicture(obj, area, sys);

    return VLC_SUCCESS;
}