#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_next_block_flags; int /*<<< orphan*/  b_frame_slice; scalar_t__ b_waiting_iframe; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* OutputFrame (TYPE_1__*) ; 

__attribute__((used)) static block_t * PacketizeDrain( void *p_private )
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_sys->b_waiting_iframe || !p_sys->b_frame_slice )
        return NULL;

    block_t *p_out = OutputFrame( p_dec );
    if( p_out )
    {
        p_out->i_flags |= p_sys->i_next_block_flags;
        p_sys->i_next_block_flags = 0;
    }

    return p_out;
}