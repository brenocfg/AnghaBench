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
typedef  int /*<<< orphan*/  iso9660_dir_t ;

/* Variables and functions */
 unsigned int ISO_BLOCKSIZE ; 
 unsigned int iso9660_get_dir_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
iso9660_check_dir_block_end(iso9660_dir_t *p_iso9660_dir, unsigned *offset)
{
  if (!iso9660_get_dir_len(p_iso9660_dir))
    {
      /*
	 Length 0 indicates that no more directory records are in this
	 block. This matches how Linux and libburn's libisofs work.

	 Note that assignment below does not exactly round up.
	 If (offset % ISO_BLOCKSIZE) == 0  then offset is incremented
	 by ISO_BLOCKSIZE, i.e. the block is skipped.
      */
      *offset += ISO_BLOCKSIZE - (*offset % ISO_BLOCKSIZE);
      return true;
    }

  if ((*offset + iso9660_get_dir_len(p_iso9660_dir) - 1) / ISO_BLOCKSIZE
      != *offset / ISO_BLOCKSIZE)
    {
      /*
	 Directory record spans over block limit.
	 Hop to next block where a new record is supposed to begin,
	 if it is not after the end of the directory data.
       */
      *offset += ISO_BLOCKSIZE - (*offset % ISO_BLOCKSIZE);
      return true;
    }

  return false;
}