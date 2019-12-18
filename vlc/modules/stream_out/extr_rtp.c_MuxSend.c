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
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_mux; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
typedef  int /*<<< orphan*/  sout_mux_t ;
typedef  int /*<<< orphan*/  sout_input_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int sout_MuxSendBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int MuxSend( sout_stream_t *p_stream, void *id, block_t *p_buffer )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_mux_t *p_mux = p_sys->p_mux;
    assert( p_mux != NULL );

    return sout_MuxSendBuffer( p_mux, (sout_input_t *)id, p_buffer );
}