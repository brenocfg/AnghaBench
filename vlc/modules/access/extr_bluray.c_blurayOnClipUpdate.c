#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_15__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_16__ {scalar_t__ clip_application_type; int /*<<< orphan*/  pl_info_lock; int /*<<< orphan*/  p_out; int /*<<< orphan*/  bluray; TYPE_2__* p_clip_info; TYPE_1__* p_pl_info; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_14__ {scalar_t__ application_type; } ;
struct TYPE_17__ {TYPE_3__ clip; } ;
struct TYPE_13__ {int video_stream_count; } ;
struct TYPE_12__ {size_t clip_count; TYPE_2__* clips; } ;
typedef  TYPE_6__ CLPI_CL ;

/* Variables and functions */
 scalar_t__ BD_CLIP_APP_TYPE_TS_MAIN_PATH_TIMED_SLIDESHOW ; 
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_DISABLE_LOW_DELAY ; 
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_ENABLE_LOW_DELAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bd_free_clpi (TYPE_6__*) ; 
 TYPE_6__* bd_get_clpi (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  blurayResetStillImage (TYPE_4__*) ; 
 int /*<<< orphan*/  blurayRestartParser (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayOnClipUpdate(demux_t *p_demux, uint32_t clip)
{
    demux_sys_t *p_sys = p_demux->p_sys;

    vlc_mutex_lock(&p_sys->pl_info_lock);

    p_sys->p_clip_info = NULL;

    if (p_sys->p_pl_info && clip < p_sys->p_pl_info->clip_count) {

        p_sys->p_clip_info = &p_sys->p_pl_info->clips[clip];

    /* Let's assume a single video track for now.
     * This may brake later, but it's enough for now.
     */
        assert(p_sys->p_clip_info->video_stream_count >= 1);
    }

    CLPI_CL *clpi = bd_get_clpi(p_sys->bluray, clip);
    if(clpi && clpi->clip.application_type != p_sys->clip_application_type)
    {
        if(p_sys->clip_application_type == BD_CLIP_APP_TYPE_TS_MAIN_PATH_TIMED_SLIDESHOW ||
           clpi->clip.application_type == BD_CLIP_APP_TYPE_TS_MAIN_PATH_TIMED_SLIDESHOW)
            blurayRestartParser(p_demux, false, false);

        if(clpi->clip.application_type == BD_CLIP_APP_TYPE_TS_MAIN_PATH_TIMED_SLIDESHOW)
            es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_ENABLE_LOW_DELAY);
        else
            es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_DISABLE_LOW_DELAY);
        bd_free_clpi(clpi);
    }

    vlc_mutex_unlock(&p_sys->pl_info_lock);

    blurayResetStillImage(p_demux);
}