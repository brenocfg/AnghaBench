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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int i_socket; int /*<<< orphan*/ * ssh_session; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  libssh2_session_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_Close (int) ; 

__attribute__((used)) static void SSHSessionDestroy( stream_t *p_access )
{
    access_sys_t* p_sys = p_access->p_sys;

    if( p_sys->ssh_session )
    {
        libssh2_session_free( p_sys->ssh_session );
        p_sys->ssh_session = NULL;
    }
    if( p_sys->i_socket >= 0 )
    {
        net_Close( p_sys->i_socket );
        p_sys->i_socket = -1;
    }
}