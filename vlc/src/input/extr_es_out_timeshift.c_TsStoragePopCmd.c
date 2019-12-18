#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  p_filer; int /*<<< orphan*/  i_cmd_r; TYPE_4__* p_cmd; } ;
typedef  TYPE_3__ ts_storage_t ;
struct TYPE_10__ {TYPE_5__* p_block; int /*<<< orphan*/  i_offset; } ;
struct TYPE_11__ {TYPE_1__ send; } ;
struct TYPE_13__ {scalar_t__ i_type; TYPE_2__ u; } ;
typedef  TYPE_4__ ts_cmd_t ;
struct TYPE_14__ {int i_buffer; struct TYPE_14__* p_buffer; int /*<<< orphan*/  i_nb_samples; int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_5__ block_t ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 scalar_t__ C_SEND ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TsStorageIsEmpty (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* block_Alloc (int) ; 
 int fread (TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TsStoragePopCmd( ts_storage_t *p_storage, ts_cmd_t *p_cmd, bool b_flush )
{
    assert( !TsStorageIsEmpty( p_storage ) );

    *p_cmd = p_storage->p_cmd[p_storage->i_cmd_r++];
    if( p_cmd->i_type == C_SEND )
    {
        block_t block;

        if( !b_flush &&
            !fseek( p_storage->p_filer, p_cmd->u.send.i_offset, SEEK_SET ) &&
            fread( &block, sizeof(block), 1, p_storage->p_filer ) == 1 )
        {
            block_t *p_block = block_Alloc( block.i_buffer );
            if( p_block )
            {
                p_block->i_dts      = block.i_dts;
                p_block->i_pts      = block.i_pts;
                p_block->i_flags    = block.i_flags;
                p_block->i_length   = block.i_length;
                p_block->i_nb_samples = block.i_nb_samples;
                p_block->i_buffer = fread( p_block->p_buffer, 1, block.i_buffer, p_storage->p_filer );
            }
            p_cmd->u.send.p_block = p_block;
        }
        else
        {
            //perror( "TsStoragePopCmd" );
            p_cmd->u.send.p_block = block_Alloc( 1 );
        }
    }
}