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
struct TYPE_4__ {int /*<<< orphan*/ * fd; } ;
struct TYPE_5__ {TYPE_1__ listen; int /*<<< orphan*/  p_stream; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int net_Accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_add_sink (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *rtp_listen_thread( void *data )
{
    sout_stream_id_sys_t *id = data;

    assert( id->listen.fd != NULL );

    for( ;; )
    {
        int fd = net_Accept( id->p_stream, id->listen.fd );
        if( fd == -1 )
            continue;
        int canc = vlc_savecancel( );
        rtp_add_sink( id, fd, true, NULL );
        vlc_restorecancel( canc );
    }

    vlc_assert_unreachable();
}