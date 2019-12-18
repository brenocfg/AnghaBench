#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sinkc; int /*<<< orphan*/  lock_sink; TYPE_2__* sinkv; } ;
typedef  TYPE_1__ sout_stream_id_sys_t ;
struct TYPE_6__ {int member_0; int rtp_fd; int /*<<< orphan*/  rtcp; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_2__ rtp_sink_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseRTCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_ERASE (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void rtp_del_sink( sout_stream_id_sys_t *id, int fd )
{
    rtp_sink_t sink = { fd, NULL };

    /* NOTE: must be safe to use if fd is not included */
    vlc_mutex_lock( &id->lock_sink );
    for( int i = 0; i < id->sinkc; i++ )
    {
        if (id->sinkv[i].rtp_fd == fd)
        {
            sink = id->sinkv[i];
            TAB_ERASE(id->sinkc, id->sinkv, i);
            break;
        }
    }
    vlc_mutex_unlock( &id->lock_sink );

    CloseRTCP( sink.rtcp );
    net_Close( sink.rtp_fd );
}