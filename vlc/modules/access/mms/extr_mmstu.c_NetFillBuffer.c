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
struct pollfd {scalar_t__ revents; void* events; int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_8__ {unsigned int i_timeout; scalar_t__ i_buffer_tcp; scalar_t__ i_proto; scalar_t__ i_buffer_udp; scalar_t__ buffer_tcp; scalar_t__ buffer_udp; int /*<<< orphan*/  i_handle_udp; int /*<<< orphan*/  i_handle_tcp; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int MMS_BUFFER_SIZE ; 
 scalar_t__ MMS_PROTO_UDP ; 
 void* POLLIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int,int) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_killed () ; 
 int vlc_poll_i11e (struct pollfd*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static int NetFillBuffer( stream_t *p_access )
{
    access_sys_t    *p_sys = p_access->p_sys;
    int             i_ret;
    struct pollfd   ufd[2];
    unsigned        timeout = p_sys->i_timeout, nfd = 0;

    /* FIXME when using udp */
    ssize_t i_tcp, i_udp;
    ssize_t i_tcp_read, i_udp_read;

    i_tcp = MMS_BUFFER_SIZE/2 - p_sys->i_buffer_tcp;

    if( p_sys->i_proto == MMS_PROTO_UDP )
    {
        i_udp = MMS_BUFFER_SIZE/2 - p_sys->i_buffer_udp;
    }
    else
    {
        i_udp = 0;  /* there isn't udp socket */
    }

    if( ( i_udp <= 0 ) && ( i_tcp <= 0 ) )
    {
        msg_Warn( p_access, "nothing to read %d:%d", (int)i_tcp, (int)i_udp );
        return 0;
    }
    else
    {
        /* msg_Warn( p_access, "ask for tcp:%d udp:%d", i_tcp, i_udp ); */
    }

    /* Initialize file descriptor set */
    if( i_tcp > 0 )
    {
        ufd[nfd].fd = p_sys->i_handle_tcp;
        ufd[nfd].events = POLLIN;
        nfd++;
    }
    if( i_udp > 0 )
    {
        ufd[nfd].fd = p_sys->i_handle_udp;
        ufd[nfd].events = POLLIN;
        nfd++;
    }

    /* Find if some data is available */
    if( p_sys->i_buffer_tcp > 0 || p_sys->i_buffer_udp > 0 )
        timeout = 2000;

    do
    {
        if( vlc_killed() )
            return -1;

        i_ret = vlc_poll_i11e(ufd, nfd, timeout);
    }
    while( i_ret < 0 && errno == EINTR ); /* FIXME: recompute timeout */

    if( i_ret == 0 )
    {
        msg_Err(p_access, "no data received");
        return -1;
    }

    if( i_ret < 0 )
    {
        msg_Err( p_access, "network poll error: %s", vlc_strerror_c(errno) );
        return -1;
    }

    i_tcp_read = i_udp_read = 0;

    if( ( i_tcp > 0 ) && ufd[0].revents )
    {
        i_tcp_read =
            recv( p_sys->i_handle_tcp,
                  p_sys->buffer_tcp + p_sys->i_buffer_tcp,
                  i_tcp + MMS_BUFFER_SIZE/2, 0 );
    }

    if( i_udp > 0 && ufd[i_tcp > 0].revents )
    {
        i_udp_read = recv( p_sys->i_handle_udp,
                           p_sys->buffer_udp + p_sys->i_buffer_udp,
                           i_udp + MMS_BUFFER_SIZE/2, 0 );
    }

#ifdef MMS_DEBUG
    if( p_sys->i_proto == MMS_PROTO_UDP )
    {
        msg_Dbg( p_access, "filling buffer TCP:%d+%d UDP:%d+%d",
                 p_sys->i_buffer_tcp, i_tcp_read,
                 p_sys->i_buffer_udp, i_udp_read );
    }
    else
    {
        msg_Dbg( p_access, "filling buffer TCP:%d+%d",
                 p_sys->i_buffer_tcp, i_tcp_read );
    }
#endif

    if( i_tcp_read > 0 ) p_sys->i_buffer_tcp += (size_t) i_tcp_read;
    if( i_udp_read > 0 ) p_sys->i_buffer_udp += (size_t) i_udp_read;

    return i_tcp_read + i_udp_read;
}