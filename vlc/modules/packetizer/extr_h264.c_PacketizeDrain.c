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
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_9__ {int /*<<< orphan*/  b_slice; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_10__ {int i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_DROP ; 
 TYPE_3__* OutputPicture (TYPE_1__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 

__attribute__((used)) static block_t * PacketizeDrain( void *p_private )
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( !p_sys->b_slice )
        return NULL;

    block_t *p_out = OutputPicture( p_dec );
    if( p_out && (p_out->i_flags & BLOCK_FLAG_DROP) )
    {
        block_Release( p_out );
        p_out = NULL;
    }

    return p_out;
}