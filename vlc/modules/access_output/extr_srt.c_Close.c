#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_poll_id; int /*<<< orphan*/  sock; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  srt_cleanup () ; 
 int /*<<< orphan*/  srt_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srt_epoll_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srt_epoll_remove_usock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_access_out_t     *p_access = (sout_access_out_t*)p_this;
    sout_access_out_sys_t *p_sys = p_access->p_sys;

    vlc_mutex_destroy( &p_sys->lock );

    srt_epoll_remove_usock( p_sys->i_poll_id, p_sys->sock );
    srt_close( p_sys->sock );
    srt_epoll_release( p_sys->i_poll_id );

    srt_cleanup();
}