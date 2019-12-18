#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p_fifo; } ;
typedef  TYPE_1__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_FifoPut (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtp_packetize_send( sout_stream_id_sys_t *id, block_t *out )
{
    block_FifoPut( id->p_fifo, out );
}