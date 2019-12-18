#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 size_t SSIZE_MAX ; 
 TYPE_1__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

block_t *vlc_stream_Block( stream_t *s, size_t size )
{
    if( unlikely(size > SSIZE_MAX) )
        return NULL;

    block_t *block = block_Alloc( size );
    if( unlikely(block == NULL) )
        return NULL;

    ssize_t val = vlc_stream_Read( s, block->p_buffer, size );
    if( val <= 0 )
    {
        block_Release( block );
        return NULL;
    }

    block->i_buffer = val;
    return block;
}