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
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_fd; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  Process (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *Run( void *data )
{
    intf_thread_t *p_intf = data;
    intf_sys_t *p_sys = p_intf->p_sys;

    struct pollfd ufd;
    ufd.fd = p_sys->i_fd;
    ufd.events = POLLIN;

    for( ;; )
    {
        /* Wait for data */
        if( poll( &ufd, 1, -1 ) == -1 )
        {
            if( errno == EINTR )
                continue;
            break;
        }

        /* Process */
        int canc = vlc_savecancel();
        Process( p_intf );
        vlc_restorecancel(canc);
    }
    return NULL;
}