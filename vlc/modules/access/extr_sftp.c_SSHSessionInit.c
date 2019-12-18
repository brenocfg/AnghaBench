#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {int i_socket; int /*<<< orphan*/ * ssh_session; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int LIBSSH2_ERROR_EAGAIN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SSHSessionDestroy (TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * libssh2_session_init () ; 
 int /*<<< orphan*/  libssh2_session_set_blocking (int /*<<< orphan*/ *,int) ; 
 int libssh2_session_startup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char const*,int) ; 
 int net_Connect (TYPE_1__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SSHSessionInit( stream_t *p_access, const char *psz_host, int i_port )
{
    access_sys_t* p_sys = p_access->p_sys;

    /* Connect to the server using a regular socket */
    assert( p_sys->i_socket == -1 );
    p_sys->i_socket = net_Connect( p_access, psz_host, i_port, SOCK_STREAM,
                                   0 );
    if( p_sys->i_socket < 0 )
        goto error;

    /* Create the ssh connexion and wait until the server answer */
    p_sys->ssh_session = libssh2_session_init();
    if( p_sys->ssh_session == NULL )
        goto error;

    int i_ret;
    while( ( i_ret = libssh2_session_startup( p_sys->ssh_session, p_sys->i_socket ) )
           == LIBSSH2_ERROR_EAGAIN );

    if( i_ret != 0 )
        goto error;

    /* Set the socket in non-blocking mode */
    libssh2_session_set_blocking( p_sys->ssh_session, 1 );
    return VLC_SUCCESS;

error:
    msg_Err( p_access, "Impossible to open the connection to %s:%i",
             psz_host, i_port );
    SSHSessionDestroy( p_access );
    return VLC_EGENERIC;
}