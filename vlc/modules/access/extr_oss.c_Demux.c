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
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {scalar_t__ i_next_demux_date; int /*<<< orphan*/  p_es; int /*<<< orphan*/  i_fd; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {scalar_t__ i_pts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 TYPE_3__* GrabAudio (TYPE_1__*) ; 
 int POLLIN ; 
 int POLLPRI ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    struct pollfd fd;
    fd.fd = p_sys->i_fd;
    fd.events = POLLIN|POLLPRI;
    fd.revents = 0;

    block_t *p_block = NULL;

    do
    {
        if( p_block )
        {
            es_out_Send( p_demux->out, p_sys->p_es, p_block );
            p_block = NULL;
        }

        /* Wait for data */
        if( poll( &fd, 1, 10 ) ) /* Timeout after 0.01 seconds. Bigger delays are an issue when used with/as an input-slave since all the inputs run in the same thread. */
        {
            if( errno == EINTR )
                continue;
            if( fd.revents & (POLLIN|POLLPRI) )
            {
                p_block = GrabAudio( p_demux );
                if( p_block )
                    es_out_SetPCR( p_demux->out, p_block->i_pts );
            }
        }
    } while( p_block && p_sys->i_next_demux_date > 0 &&
             p_block->i_pts < p_sys->i_next_demux_date );

    if( p_block )
        es_out_Send( p_demux->out, p_sys->p_es, p_block );

    return 1;
}