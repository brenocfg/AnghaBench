#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
struct TYPE_10__ {scalar_t__ magic; struct TYPE_10__* description; TYPE_1__* bitmap_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* free_bmap ) (TYPE_2__*) ;int /*<<< orphan*/  (* print_stats ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_free_generic_bitmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_free_mem (TYPE_2__**) ; 
 int /*<<< orphan*/  ext2fs_print_bmap_statistics (TYPE_2__*) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

void ext2fs_free_generic_bmap(ext2fs_generic_bitmap gen_bmap)
{
	ext2fs_generic_bitmap_64 bmap = (ext2fs_generic_bitmap_64) gen_bmap;

	if (!bmap)
		return;

	if (EXT2FS_IS_32_BITMAP(bmap)) {
		ext2fs_free_generic_bitmap(gen_bmap);
		return;
	}

	if (!EXT2FS_IS_64_BITMAP(bmap))
		return;

#ifdef ENABLE_BMAP_STATS
	if (getenv("E2FSPROGS_BITMAP_STATS")) {
		ext2fs_print_bmap_statistics(bmap);
		bmap->bitmap_ops->print_stats(bmap);
	}
#endif

	bmap->bitmap_ops->free_bmap(bmap);

	if (bmap->description) {
		ext2fs_free_mem(&bmap->description);
		bmap->description = 0;
	}
	bmap->magic = 0;
	ext2fs_free_mem(&bmap);
}