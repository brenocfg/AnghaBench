#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  TYPE_2__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  TYPE_3__* block_entry_t ;
struct TYPE_24__ {int i_flags; } ;
struct TYPE_23__ {int /*<<< orphan*/  sha; int /*<<< orphan*/  physblock; } ;
struct TYPE_22__ {int flags; unsigned int pos; TYPE_8__ inode; int /*<<< orphan*/  ino; int /*<<< orphan*/  physblock; int /*<<< orphan*/  blockno; scalar_t__ buf; TYPE_1__* fs; } ;
struct TYPE_21__ {unsigned int blocksize; int flags; int /*<<< orphan*/  block_sha_map; } ;

/* Variables and functions */
 int BMAP_ALLOC ; 
 int /*<<< orphan*/  BMAP_BUFFER ; 
 int BMAP_SET ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_FILE_RO ; 
 scalar_t__ EXT2_ET_INLINE_DATA_NO_SPACE ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2_FILE ; 
 scalar_t__ EXT2_ET_NO_MEMORY ; 
 int EXT2_FILE_BUF_DIRTY ; 
 int EXT2_FILE_WRITE ; 
 int EXT2_FLAG_SHARE_DUP ; 
 unsigned int EXT2_I_SIZE (TYPE_8__*) ; 
 int EXT4_INLINE_DATA_FL ; 
 TYPE_3__* calloc (int,int) ; 
 scalar_t__ ext2fs_bmap2 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_file_set_size2 (TYPE_2__*,unsigned int) ; 
 scalar_t__ ext2fs_file_write_inline_data (TYPE_2__*,void const*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  ext2fs_hashmap_add (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ext2fs_hashmap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext2fs_iblk_add_blocks (TYPE_1__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  ext2fs_sha512 (unsigned char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_write_inode (TYPE_1__*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ load_buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,unsigned int) ; 
 scalar_t__ sync_buffer_position (TYPE_2__*) ; 

errcode_t ext2fs_file_write(ext2_file_t file, const void *buf,
			    unsigned int nbytes, unsigned int *written)
{
	ext2_filsys	fs;
	errcode_t	retval = 0;
	unsigned int	start, c, count = 0;
	const char	*ptr = (const char *) buf;
	block_entry_t	new_block = NULL, old_block = NULL;
	int		bmap_flags = 0;

	EXT2_CHECK_MAGIC(file, EXT2_ET_MAGIC_EXT2_FILE);
	fs = file->fs;

	if (!(file->flags & EXT2_FILE_WRITE))
		return EXT2_ET_FILE_RO;

	/* If an inode has inline data, things get complicated. */
	if (file->inode.i_flags & EXT4_INLINE_DATA_FL) {
		retval = ext2fs_file_write_inline_data(file, buf, nbytes,
						       written);
		if (retval != EXT2_ET_INLINE_DATA_NO_SPACE)
			return retval;
		/* fall through to read data from the block */
		retval = 0;
	}

	while (nbytes > 0) {
		retval = sync_buffer_position(file);
		if (retval)
			goto fail;

		start = file->pos % fs->blocksize;
		c = fs->blocksize - start;
		if (c > nbytes)
			c = nbytes;

		/*
		 * We only need to do a read-modify-update cycle if
		 * we're doing a partial write.
		 */
		retval = load_buffer(file, (c == fs->blocksize));
		if (retval)
			goto fail;

		file->flags |= EXT2_FILE_BUF_DIRTY;
		memcpy(file->buf+start, ptr, c);

		/*
		 * OK, the physical block hasn't been allocated yet.
		 * Allocate it.
		 */
		if (!file->physblock) {
			bmap_flags = (file->ino ? BMAP_ALLOC : 0);
			if (fs->flags & EXT2_FLAG_SHARE_DUP) {
				new_block = calloc(1, sizeof(*new_block));
				if (!new_block) {
					retval = EXT2_ET_NO_MEMORY;
					goto fail;
				}
				ext2fs_sha512((const unsigned char*)file->buf,
						fs->blocksize, new_block->sha);
				old_block = ext2fs_hashmap_lookup(
							fs->block_sha_map,
							new_block->sha,
							sizeof(new_block->sha));
			}

			if (old_block) {
				file->physblock = old_block->physblock;
				bmap_flags |= BMAP_SET;
				free(new_block);
				new_block = NULL;
			}

			retval = ext2fs_bmap2(fs, file->ino, &file->inode,
					      BMAP_BUFFER,
					      bmap_flags,
					      file->blockno, 0,
					      &file->physblock);
			if (retval) {
				free(new_block);
				new_block = NULL;
				goto fail;
			}

			if (new_block) {
				new_block->physblock = file->physblock;
				ext2fs_hashmap_add(fs->block_sha_map, new_block,
					new_block->sha, sizeof(new_block->sha));
			}

			if (bmap_flags & BMAP_SET) {
				ext2fs_iblk_add_blocks(fs, &file->inode, 1);
				ext2fs_write_inode(fs, file->ino, &file->inode);
			}
		}

		file->pos += c;
		ptr += c;
		count += c;
		nbytes -= c;
	}

fail:
	/* Update inode size */
	if (count != 0 && EXT2_I_SIZE(&file->inode) < file->pos) {
		errcode_t	rc;

		rc = ext2fs_file_set_size2(file, file->pos);
		if (retval == 0)
			retval = rc;
	}

	if (written)
		*written = count;
	return retval;
}