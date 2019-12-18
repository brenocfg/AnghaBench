#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  i_port; int /*<<< orphan*/  psz_host; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct vlc_memstream {scalar_t__ length; int /*<<< orphan*/  ptr; } ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_10__ {int /*<<< orphan*/ * stream; TYPE_1__ url; TYPE_1__ proxy; scalar_t__ b_proxy; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char*) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_tls_SocketOpenTCP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tls_Write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int OpenConnection( stream_t *p_access,
                           struct vlc_memstream *restrict stream )
{
    access_sys_t *p_sys = p_access->p_sys;
    const vlc_url_t *srv = p_sys->b_proxy ? &p_sys->proxy : &p_sys->url;

    /* XXX: This is useless: HTTP/1.0 closes connection by default */
    vlc_memstream_puts( stream, "Connection: Close\r\n" );

    vlc_memstream_puts( stream, "\r\n" ); /* end of HTTP request header */

    if( vlc_memstream_close( stream ) )
        return VLC_ENOMEM;

    vlc_tls_t *sock = vlc_tls_SocketOpenTCP( VLC_OBJECT(p_access),
                                             srv->psz_host, srv->i_port );
    if( sock == NULL )
    {
        free( stream->ptr );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_access, "sending request:\n%s", stream->ptr );

    ssize_t val = vlc_tls_Write( sock, stream->ptr, stream->length );
    free( stream->ptr );
    if( val < (ssize_t)stream->length )
    {
        msg_Err( p_access, "failed to send request" );
        vlc_tls_Close( sock );
        stream = NULL;
    }

    p_sys->stream = sock;
    return (sock != NULL) ? VLC_SUCCESS : VLC_EGENERIC;
}