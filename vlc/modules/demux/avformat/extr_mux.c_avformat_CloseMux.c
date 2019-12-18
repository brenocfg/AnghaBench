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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_6__ {struct TYPE_6__* io_buffer; int /*<<< orphan*/  io; int /*<<< orphan*/  oc; int /*<<< orphan*/  b_error; int /*<<< orphan*/  b_write_header; } ;
typedef  TYPE_2__ sout_mux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 scalar_t__ av_write_trailer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

void avformat_CloseMux( vlc_object_t *p_this )
{
    sout_mux_t *p_mux = (sout_mux_t*)p_this;
    sout_mux_sys_t *p_sys = p_mux->p_sys;

    if( !p_sys->b_write_header && !p_sys->b_error && av_write_trailer( p_sys->oc ) < 0 )
    {
        msg_Err( p_mux, "could not write trailer" );
    }

    avformat_free_context(p_sys->oc);
    av_free(p_sys->io);

    free( p_sys->io_buffer );
    free( p_sys );
}