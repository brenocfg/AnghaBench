#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ projection_mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  force; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;int /*<<< orphan*/  control; int /*<<< orphan*/  display; int /*<<< orphan*/  prepare; TYPE_4__* sys; TYPE_2__ source; TYPE_1__ obj; } ;
typedef  TYPE_3__ vout_display_t ;
struct TYPE_14__ {int /*<<< orphan*/  sys; int /*<<< orphan*/  area; } ;
typedef  TYPE_4__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (TYPE_3__*) ; 
 int /*<<< orphan*/  CommonInit (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ CommonWindowInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Display ; 
 scalar_t__ Init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ PROJECTION_MODE_RECTANGULAR ; 
 int /*<<< orphan*/  Prepare ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int VLC_SUCCESS ; 
 TYPE_4__* calloc (int,int) ; 

__attribute__((used)) static int Open(vout_display_t *vd, const vout_display_cfg_t *cfg,
                video_format_t *fmtp, vlc_video_context *context)
{
    vout_display_sys_t *sys;

    if ( !vd->obj.force && vd->source.projection_mode != PROJECTION_MODE_RECTANGULAR)
        return VLC_EGENERIC; /* let a module who can handle it do it */

    vd->sys = sys = calloc(1, sizeof(*sys));
    if (!sys)
        return VLC_ENOMEM;

    CommonInit(vd, &sys->area, cfg);
    if (CommonWindowInit(VLC_OBJECT(vd), &sys->area, &sys->sys, false))
        goto error;

    /* */
    if (Init(vd, fmtp))
        goto error;

    /* */
    vd->prepare = Prepare;
    vd->display = Display;
    vd->control = Control;
    vd->close = Close;
    return VLC_SUCCESS;

error:
    Close(vd);
    return VLC_EGENERIC;
}