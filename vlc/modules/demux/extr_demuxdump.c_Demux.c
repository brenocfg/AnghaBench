#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_access_out_t ;
struct TYPE_8__ {int /*<<< orphan*/  s; scalar_t__ p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {int i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_BLOCKSIZE ; 
 TYPE_2__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 size_t sout_AccessOutWrite (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    sout_access_out_t *out = (void *)p_demux->p_sys;

    block_t *block = block_Alloc( DUMP_BLOCKSIZE );
    if( unlikely(block == NULL) )
        return -1;

    int rd = vlc_stream_Read( p_demux->s, block->p_buffer, DUMP_BLOCKSIZE );
    if ( rd <= 0 )
    {
        block_Release( block );
        return rd;
    }
    block->i_buffer = rd;

    size_t wr = sout_AccessOutWrite( out, block );
    if( wr != (size_t)rd )
    {
        msg_Err( p_demux, "cannot write data" );
        return -1;
    }
    return 1;
}