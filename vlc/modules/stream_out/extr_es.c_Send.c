#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_input; int /*<<< orphan*/  p_mux; } ;
typedef  TYPE_1__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int sout_MuxSendBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *_id, block_t *p_buffer )
{
    VLC_UNUSED(p_stream);
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    return sout_MuxSendBuffer( id->p_mux, id->p_input, p_buffer );
}