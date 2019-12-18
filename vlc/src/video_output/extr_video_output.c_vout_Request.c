#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* p; } ;
typedef  TYPE_1__ vout_thread_t ;
struct TYPE_17__ {float rate; scalar_t__ spu; int /*<<< orphan*/  thread; int /*<<< orphan*/  original; scalar_t__ delay; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * display; } ;
typedef  TYPE_2__ vout_thread_sys_t ;
struct TYPE_18__ {int /*<<< orphan*/ * clock; int /*<<< orphan*/ * fmt; TYPE_1__* vout; } ;
typedef  TYPE_3__ vout_configuration_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  input_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  Thread ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_OUTPUT ; 
 int /*<<< orphan*/  VoutCheckFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VoutFixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  spu_Attach (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vout_ChangeSource (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_DisableWindow (TYPE_1__*) ; 
 scalar_t__ vout_EnableWindow (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_IntfReinit (TYPE_1__*) ; 
 int /*<<< orphan*/  vout_ReinitInterlacingSupport (TYPE_1__*) ; 
 int /*<<< orphan*/  vout_ReleaseDisplay (TYPE_1__*) ; 
 scalar_t__ vout_Start (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  vout_StopDisplay (TYPE_1__*) ; 

int vout_Request(const vout_configuration_t *cfg, vlc_video_context *vctx, input_thread_t *input)
{
    vout_thread_t *vout = cfg->vout;
    vout_thread_sys_t *sys = vout->p;

    assert(cfg->fmt != NULL);
    assert(cfg->clock != NULL);

    if (!VoutCheckFormat(cfg->fmt))
        /* don't stop the display and keep sys->original */
        return -1;

    video_format_t original;
    VoutFixFormat(&original, cfg->fmt);

    if (vout_ChangeSource(vout, &original) == 0)
    {
        video_format_Clean(&original);
        return 0;
    }

    if (vout_EnableWindow(vout, &original, NULL) != 0)
    {
        /* the window was not enabled, nor the display started */
        msg_Err(vout, "failed to enable window");
        video_format_Clean(&original);
        return -1;
    }

    if (sys->display != NULL)
        vout_StopDisplay(vout);

    vout_ReinitInterlacingSupport(vout);

    sys->original = original;

    sys->delay = 0;
    sys->rate = 1.f;
    sys->clock = cfg->clock;
    sys->delay = 0;

    if (vout_Start(vout, vctx, cfg))
    {
        msg_Err(vout, "video output display creation failed");
        video_format_Clean(&sys->original);
        vout_DisableWindow(vout);
        return -1;
    }
    if (vlc_clone(&sys->thread, Thread, vout, VLC_THREAD_PRIORITY_OUTPUT)) {
        vout_ReleaseDisplay(vout);
        vout_DisableWindow(vout);
        return -1;
    }

    if (input != NULL && sys->spu)
        spu_Attach(sys->spu, input);
    vout_IntfReinit(vout);
    return 0;
}