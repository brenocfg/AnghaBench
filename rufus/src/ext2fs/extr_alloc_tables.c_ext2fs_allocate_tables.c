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
struct ext2fs_numeric_progress_struct {int dummy; } ;
typedef  TYPE_2__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ dgrp_t ;
struct TYPE_9__ {scalar_t__ group_desc_count; TYPE_1__* progress_ops; int /*<<< orphan*/  block_map; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* close ) (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update ) (TYPE_2__*,struct ext2fs_numeric_progress_struct*,scalar_t__) ;int /*<<< orphan*/  (* init ) (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ext2fs_allocate_group_table (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,struct ext2fs_numeric_progress_struct*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *) ; 

errcode_t ext2fs_allocate_tables(ext2_filsys fs)
{
	errcode_t	retval;
	dgrp_t		i;
	struct ext2fs_numeric_progress_struct progress;

	if (fs->progress_ops && fs->progress_ops->init)
		(fs->progress_ops->init)(fs, &progress, NULL,
					 fs->group_desc_count);

	for (i = 0; i < fs->group_desc_count; i++) {
		if (fs->progress_ops && fs->progress_ops->update)
			(fs->progress_ops->update)(fs, &progress, i);
		retval = ext2fs_allocate_group_table(fs, i, fs->block_map);
		if (retval)
			return retval;
	}
	if (fs->progress_ops && fs->progress_ops->close)
		(fs->progress_ops->close)(fs, &progress, NULL);
	return 0;
}