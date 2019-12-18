#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_11__ {int /*<<< orphan*/  sem; TYPE_6__* component; scalar_t__ filtered_pictures; TYPE_5__* output; TYPE_5__* input; } ;
typedef  TYPE_2__ filter_sys_t ;
struct TYPE_14__ {scalar_t__ is_enabled; TYPE_5__* control; } ;
struct TYPE_13__ {scalar_t__ is_enabled; } ;
struct TYPE_12__ {scalar_t__ user_data; } ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_host_deinit () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_component_disable (TYPE_6__*) ; 
 int /*<<< orphan*/  mmal_component_release (TYPE_6__*) ; 
 int /*<<< orphan*/  mmal_port_disable (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 TYPE_3__* mmal_queue_get (scalar_t__) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(filter_t *filter)
{
    filter_sys_t *sys = filter->p_sys;
    MMAL_BUFFER_HEADER_T *buffer;

    if (!sys)
        return;

    if (sys->component && sys->component->control->is_enabled)
        mmal_port_disable(sys->component->control);

    if (sys->input && sys->input->is_enabled)
        mmal_port_disable(sys->input);

    if (sys->output && sys->output->is_enabled)
        mmal_port_disable(sys->output);

    if (sys->component && sys->component->is_enabled)
        mmal_component_disable(sys->component);

    while ((buffer = mmal_queue_get(sys->filtered_pictures))) {
        picture_t *pic = (picture_t *)buffer->user_data;
        picture_Release(pic);
    }

    if (sys->filtered_pictures)
        mmal_queue_destroy(sys->filtered_pictures);

    if (sys->component)
        mmal_component_release(sys->component);

    vlc_sem_destroy(&sys->sem);
    free(sys);

    bcm_host_deinit();
}