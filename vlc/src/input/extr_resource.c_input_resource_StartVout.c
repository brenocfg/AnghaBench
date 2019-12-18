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
struct TYPE_12__ {TYPE_1__* fmt; int /*<<< orphan*/  vout; } ;
typedef  TYPE_2__ vout_configuration_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_input; } ;
typedef  TYPE_3__ input_resource_t ;
struct TYPE_14__ {int /*<<< orphan*/  viewpoint; } ;
typedef  TYPE_4__ input_control_param_t ;
struct TYPE_11__ {int /*<<< orphan*/  pose; } ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayVoutTitle (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_CONTROL_SET_INITIAL_VIEWPOINT ; 
 int /*<<< orphan*/  input_ControlPush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  input_resource_PutVoutLocked (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vout_Request (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int input_resource_StartVout(input_resource_t *p_resource,
                              vlc_video_context *vctx,
                              const vout_configuration_t *cfg)
{
    vlc_mutex_lock( &p_resource->lock );
    if (vout_Request(cfg, vctx, p_resource->p_input)) {
        input_resource_PutVoutLocked(p_resource, cfg->vout);
        vlc_mutex_unlock(&p_resource->lock);
        return -1;
    }

    DisplayVoutTitle(p_resource, cfg->vout);

    /* Send original viewpoint to the input in order to update other ESes */
    if (p_resource->p_input != NULL)
    {
        input_control_param_t param = { .viewpoint = cfg->fmt->pose };
        input_ControlPush(p_resource->p_input, INPUT_CONTROL_SET_INITIAL_VIEWPOINT,
                          &param);
    }
    vlc_mutex_unlock( &p_resource->lock );
    return 0;
}