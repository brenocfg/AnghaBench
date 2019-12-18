#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct stream_ctrl {struct stream_ctrl* content_type; struct stream_ctrl* buffer; struct stream_ctrl* next; struct stream_ctrl* controls; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_data; int /*<<< orphan*/  wait_space; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  thread; } ;
struct TYPE_2__ {struct stream_ctrl* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  struct stream_ctrl stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct stream_ctrl*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_interrupt_kill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    stream_t *stream = (stream_t *)obj;
    stream_sys_t *sys = stream->p_sys;

    vlc_cancel(sys->thread);
    vlc_interrupt_kill(sys->interrupt);
    vlc_join(sys->thread, NULL);
    vlc_interrupt_destroy(sys->interrupt);
    vlc_cond_destroy(&sys->wait_space);
    vlc_cond_destroy(&sys->wait_data);
    vlc_mutex_destroy(&sys->lock);

    while(sys->controls)
    {
        struct stream_ctrl *ctrl = sys->controls;
        sys->controls = ctrl->next;
        free(ctrl);
    }
    free(sys->buffer);
    free(sys->content_type);
    free(sys);
}