#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_reorder_depth; int /*<<< orphan*/  i_708_channels; int /*<<< orphan*/  i_608_channels; } ;
typedef  TYPE_1__ decoder_cc_desc_t ;
struct TYPE_12__ {scalar_t__ b_reorder; int /*<<< orphan*/  i_708channels; int /*<<< orphan*/  i_608channels; int /*<<< orphan*/  i_data; int /*<<< orphan*/  p_data; } ;
struct TYPE_10__ {int i_flags; TYPE_7__ current; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_2__ cc_storage_t ;
struct TYPE_11__ {int i_flags; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_TYPE_MASK ; 
 TYPE_3__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_Flush (TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

block_t * cc_storage_get_current( cc_storage_t *p_ccs, decoder_cc_desc_t *p_desc )
{
    block_t *p_block;

    if( !p_ccs->current.b_reorder && p_ccs->current.i_data <= 0 )
        return NULL;

    p_block = block_Alloc( p_ccs->current.i_data);
    if( p_block )
    {
        memcpy( p_block->p_buffer, p_ccs->current.p_data, p_ccs->current.i_data );
        p_block->i_dts =
        p_block->i_pts = p_ccs->current.b_reorder ? p_ccs->i_pts : p_ccs->i_dts;
        p_block->i_flags = p_ccs->i_flags & BLOCK_FLAG_TYPE_MASK;

        p_desc->i_608_channels = p_ccs->current.i_608channels;
        p_desc->i_708_channels = p_ccs->current.i_708channels;
        p_desc->i_reorder_depth = p_ccs->current.b_reorder ? 4 : -1;
    }
    cc_Flush( &p_ccs->current );

    return p_block;
}