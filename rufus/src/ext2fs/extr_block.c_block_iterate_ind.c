#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct block_context {int flags; int (* func ) (TYPE_1__*,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  priv_data; TYPE_1__* fs; scalar_t__ errcode; scalar_t__ ind_buf; scalar_t__ bcount; } ;
typedef  scalar_t__ blk_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_9__ {scalar_t__ s_first_data_block; } ;
struct TYPE_8__ {int blocksize; TYPE_7__* super; } ;

/* Variables and functions */
 int BLOCK_ABORT ; 
 int BLOCK_CHANGED ; 
 scalar_t__ BLOCK_COUNT_IND ; 
 int BLOCK_ERROR ; 
 int BLOCK_FLAG_APPEND ; 
 int BLOCK_FLAG_DATA_ONLY ; 
 int BLOCK_FLAG_DEPTH_TRAVERSE ; 
 scalar_t__ EXT2_ET_BAD_IND_BLOCK ; 
 int /*<<< orphan*/  check_for_ro_violation_return (struct block_context*,int) ; 
 scalar_t__ ext2fs_blocks_count (TYPE_7__*) ; 
 scalar_t__ ext2fs_read_ind_block (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ ext2fs_write_ind_block (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int stub1 (TYPE_1__*,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_1__*,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_1__*,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int stub4 (TYPE_1__*,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int block_iterate_ind(blk_t *ind_block, blk_t ref_block,
			     int ref_offset, struct block_context *ctx)
{
	int	ret = 0, changed = 0;
	int	i, flags, limit, offset;
	blk_t	*block_nr;
	blk64_t	blk64;

	limit = ctx->fs->blocksize >> 2;
	if (!(ctx->flags & BLOCK_FLAG_DEPTH_TRAVERSE) &&
	    !(ctx->flags & BLOCK_FLAG_DATA_ONLY)) {
		blk64 = *ind_block;
		ret = (*ctx->func)(ctx->fs, &blk64,
				   BLOCK_COUNT_IND, ref_block,
				   ref_offset, ctx->priv_data);
		*ind_block = blk64;
	}
	check_for_ro_violation_return(ctx, ret);
	if (!*ind_block || (ret & BLOCK_ABORT)) {
		ctx->bcount += limit;
		return ret;
	}
	if (*ind_block >= ext2fs_blocks_count(ctx->fs->super) ||
	    *ind_block < ctx->fs->super->s_first_data_block) {
		ctx->errcode = EXT2_ET_BAD_IND_BLOCK;
		ret |= BLOCK_ERROR;
		return ret;
	}
	ctx->errcode = ext2fs_read_ind_block(ctx->fs, *ind_block,
					     ctx->ind_buf);
	if (ctx->errcode) {
		ret |= BLOCK_ERROR;
		return ret;
	}

	block_nr = (blk_t *) ctx->ind_buf;
	offset = 0;
	if (ctx->flags & BLOCK_FLAG_APPEND) {
		for (i = 0; i < limit; i++, ctx->bcount++, block_nr++) {
			blk64 = *block_nr;
			flags = (*ctx->func)(ctx->fs, &blk64, ctx->bcount,
					     *ind_block, offset,
					     ctx->priv_data);
			*block_nr = blk64;
			changed	|= flags;
			if (flags & BLOCK_ABORT) {
				ret |= BLOCK_ABORT;
				break;
			}
			offset += sizeof(blk_t);
		}
	} else {
		for (i = 0; i < limit; i++, ctx->bcount++, block_nr++) {
			if (*block_nr == 0)
				goto skip_sparse;
			blk64 = *block_nr;
			flags = (*ctx->func)(ctx->fs, &blk64, ctx->bcount,
					     *ind_block, offset,
					     ctx->priv_data);
			*block_nr = blk64;
			changed	|= flags;
			if (flags & BLOCK_ABORT) {
				ret |= BLOCK_ABORT;
				break;
			}
		skip_sparse:
			offset += sizeof(blk_t);
		}
	}
	check_for_ro_violation_return(ctx, changed);
	if (changed & BLOCK_CHANGED) {
		ctx->errcode = ext2fs_write_ind_block(ctx->fs, *ind_block,
						      ctx->ind_buf);
		if (ctx->errcode)
			ret |= BLOCK_ERROR | BLOCK_ABORT;
	}
	if ((ctx->flags & BLOCK_FLAG_DEPTH_TRAVERSE) &&
	    !(ctx->flags & BLOCK_FLAG_DATA_ONLY) &&
	    !(ret & BLOCK_ABORT)) {
		blk64 = *ind_block;
		ret |= (*ctx->func)(ctx->fs, &blk64,
				    BLOCK_COUNT_IND, ref_block,
				    ref_offset, ctx->priv_data);
		*ind_block = blk64;
	}
	check_for_ro_violation_return(ctx, ret);
	return ret;
}