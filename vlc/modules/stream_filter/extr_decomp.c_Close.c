#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int read_fd; int write_fd; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; scalar_t__ pid; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    stream_t *stream = (stream_t *)obj;
    stream_sys_t *p_sys = stream->p_sys;
    int status;

    vlc_cancel (p_sys->thread);
    vlc_close (p_sys->read_fd);
    vlc_join (p_sys->thread, NULL);
    if (p_sys->write_fd != -1)
        /* Killed before EOF? */
        vlc_close (p_sys->write_fd);

    msg_Dbg (obj, "waiting for PID %u", (unsigned)p_sys->pid);
    while (waitpid (p_sys->pid, &status, 0) == -1);
    msg_Dbg (obj, "exit status %d", status);

    vlc_mutex_destroy (&p_sys->lock);
    vlc_cond_destroy (&p_sys->wait);
    free (p_sys);
}