#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_9__ {int /*<<< orphan*/  sem; TYPE_4__* component; scalar_t__ output_pool; scalar_t__ output_format; scalar_t__ input_pool; TYPE_3__* output; TYPE_3__* input; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_11__ {scalar_t__ is_enabled; TYPE_3__* control; } ;
struct TYPE_10__ {scalar_t__ is_enabled; } ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_host_deinit () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_component_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_component_release (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_format_free (scalar_t__) ; 
 int /*<<< orphan*/  mmal_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mmal_port_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CloseDecoder(decoder_t *dec)
{
    decoder_sys_t *sys = dec->p_sys;
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

    if (sys->input_pool)
        mmal_pool_destroy(sys->input_pool);

    if (sys->output_format)
        mmal_format_free(sys->output_format);

    if (sys->output_pool)
        mmal_pool_destroy(sys->output_pool);

    if (sys->component)
        mmal_component_release(sys->component);

    vlc_sem_destroy(&sys->sem);
    free(sys);

    bcm_host_deinit();
}