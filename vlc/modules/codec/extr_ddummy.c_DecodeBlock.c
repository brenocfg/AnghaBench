#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {scalar_t__ i_buffer; int i_flags; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static int DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    FILE *stream = (void *)p_dec->p_sys;

    if( !p_block ) return VLCDEC_SUCCESS;

    if( stream != NULL
     && p_block->i_buffer > 0
     && !(p_block->i_flags & (BLOCK_FLAG_CORRUPTED)) )
    {
        fwrite( p_block->p_buffer, 1, p_block->i_buffer, stream );
        msg_Dbg( p_dec, "dumped %zu bytes", p_block->i_buffer );
    }
    block_Release( p_block );

    return VLCDEC_SUCCESS;
}