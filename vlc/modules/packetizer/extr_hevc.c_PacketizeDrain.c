#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_6__ {scalar_t__ p_chain; } ;
struct TYPE_8__ {scalar_t__ sets; scalar_t__ b_recovery_point; TYPE_1__ frame; } ;
typedef  TYPE_3__ decoder_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GatherAndValidateChain (int /*<<< orphan*/ *) ; 
 scalar_t__ MISSING ; 
 int /*<<< orphan*/ * OutputQueues (TYPE_3__*,int) ; 
 int /*<<< orphan*/  SetOutputBlockProperties (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t * PacketizeDrain(void *p_private)
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    block_t *p_out = NULL;

    if( p_sys->frame.p_chain &&
        p_sys->sets != MISSING &&
        p_sys->b_recovery_point )
    {
        p_out = OutputQueues(p_sys, true);
        if( p_out )
        {
            p_out = GatherAndValidateChain(p_out);
            if( p_out )
                SetOutputBlockProperties( p_dec, p_out );
        }
    }
    return p_out;
}