#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {scalar_t__ p_access; } ;
typedef  TYPE_2__ event_thread_t ;
struct TYPE_11__ {int revents; } ;
struct TYPE_10__ {int /*<<< orphan*/  p_raw1394; TYPE_5__ raw1394_poll; int /*<<< orphan*/  i_node; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVCPlay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EINTR ; 
 int POLLIN ; 
 int POLLPRI ; 
 int /*<<< orphan*/  Raw1394EventThreadCleanup ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int poll (TYPE_5__*,int,int) ; 
 int raw1394_loop_iterate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static void* Raw1394EventThread( void *obj )
{
    event_thread_t *p_ev = (event_thread_t *)obj;
    stream_t *p_access = (stream_t *) p_ev->p_access;
    access_sys_t *p_sys = (access_sys_t *) p_access->p_sys;
    int result = 0;
    int canc = vlc_savecancel();

    AVCPlay( p_access, p_sys->i_node );
    vlc_cleanup_push( Raw1394EventThreadCleanup, p_ev );
    vlc_restorecancel( canc );

    for( ;; )
    {
        while( ( result = poll( &p_sys->raw1394_poll, 1, -1 ) ) < 0 )
        {
            if( errno != EINTR )
                msg_Err( p_access, "poll error: %s", vlc_strerror_c(errno) );
        }

        if( result > 0 && ( ( p_sys->raw1394_poll.revents & POLLIN )
                         || ( p_sys->raw1394_poll.revents & POLLPRI ) ) )
        {
            canc = vlc_savecancel();
            result = raw1394_loop_iterate( p_sys->p_raw1394 );
            vlc_restorecancel( canc );
        }
    }

    vlc_cleanup_pop();
    vlc_assert_unreachable();
}