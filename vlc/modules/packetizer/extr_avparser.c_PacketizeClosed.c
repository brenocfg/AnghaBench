#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *PacketizeClosed ( decoder_t *p_dec, block_t **pp_block )
{
    (void) p_dec;
    if( pp_block != NULL && *pp_block != NULL )
        block_Release( *pp_block );
    return NULL;
}