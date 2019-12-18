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
typedef  int /*<<< orphan*/  sout_buffer_chain_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BufferChainGet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BufferChainInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void BufferChainClean( sout_buffer_chain_t *c )
{
    block_t *b;

    while( ( b = BufferChainGet( c ) ) )
    {
        block_Release( b );
    }
    BufferChainInit( c );
}