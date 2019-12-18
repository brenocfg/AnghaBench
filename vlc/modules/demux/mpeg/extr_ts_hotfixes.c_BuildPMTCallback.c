#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p_pmt; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_3__ ts_pid_t ;
struct TYPE_10__ {struct TYPE_10__* p_next; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ TYPE_PMT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  dvbpsi_packet_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BuildPMTCallback( void *p_opaque, block_t *p_block )
{
    ts_pid_t *program_pid = (ts_pid_t *) p_opaque;
    assert(program_pid->type == TYPE_PMT);
    while( p_block )
    {
        dvbpsi_packet_push( program_pid->u.p_pmt->handle,
                            p_block->p_buffer );
        block_t *p_next = p_block->p_next;
        block_Release( p_block );
        p_block = p_next;
    }
}