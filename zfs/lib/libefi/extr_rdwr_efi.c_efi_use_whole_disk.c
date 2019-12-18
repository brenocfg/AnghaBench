#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct dk_gpt {int efi_nparts; int efi_first_u_lba; int efi_last_lba; int efi_altern_lba; int efi_last_u_lba; TYPE_1__* efi_parts; } ;
typedef  scalar_t__ diskaddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ p_start; scalar_t__ p_size; scalar_t__ p_tag; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int EFI_MIN_RESV_SIZE ; 
 scalar_t__ P2ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARTITION_END_ALIGNMENT ; 
 int VT_EINVAL ; 
 int VT_ENOSPC ; 
 scalar_t__ V_RESERVED ; 
 int efi_alloc_and_read (int,struct dk_gpt**) ; 
 scalar_t__ efi_debug ; 
 int /*<<< orphan*/  efi_free (struct dk_gpt*) ; 
 int efi_write (int,struct dk_gpt*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int
efi_use_whole_disk(int fd)
{
	struct dk_gpt		*efi_label = NULL;
	int			rval;
	int			i;
	uint_t			resv_index = 0, data_index = 0;
	diskaddr_t		resv_start = 0, data_start = 0;
	diskaddr_t		data_size, limit, difference;
	boolean_t		sync_needed = B_FALSE;
	uint_t			nblocks;

	rval = efi_alloc_and_read(fd, &efi_label);
	if (rval < 0) {
		if (efi_label != NULL)
			efi_free(efi_label);
		return (rval);
	}

	/*
	 * Find the last physically non-zero partition.
	 * This should be the reserved partition.
	 */
	for (i = 0; i < efi_label->efi_nparts; i ++) {
		if (resv_start < efi_label->efi_parts[i].p_start) {
			resv_start = efi_label->efi_parts[i].p_start;
			resv_index = i;
		}
	}

	/*
	 * Find the last physically non-zero partition before that.
	 * This is the data partition.
	 */
	for (i = 0; i < resv_index; i ++) {
		if (data_start < efi_label->efi_parts[i].p_start) {
			data_start = efi_label->efi_parts[i].p_start;
			data_index = i;
		}
	}
	data_size = efi_label->efi_parts[data_index].p_size;

	/*
	 * See the "efi_alloc_and_init" function for more information
	 * about where this "nblocks" value comes from.
	 */
	nblocks = efi_label->efi_first_u_lba - 1;

	/*
	 * Determine if the EFI label is out of sync. We check that:
	 *
	 * 1. the data partition ends at the limit we set, and
	 * 2. the reserved partition starts at the limit we set.
	 *
	 * If either of these conditions is not met, then we need to
	 * resync the EFI label.
	 *
	 * The limit is the last usable LBA, determined by the last LBA
	 * and the first usable LBA fields on the EFI label of the disk
	 * (see the lines directly above). Additionally, we factor in
	 * EFI_MIN_RESV_SIZE (per its use in "zpool_label_disk") and
	 * P2ALIGN it to ensure the partition boundaries are aligned
	 * (for performance reasons). The alignment should match the
	 * alignment used by the "zpool_label_disk" function.
	 */
	limit = P2ALIGN(efi_label->efi_last_lba - nblocks - EFI_MIN_RESV_SIZE,
	    PARTITION_END_ALIGNMENT);
	if (data_start + data_size != limit || resv_start != limit)
		sync_needed = B_TRUE;

	if (efi_debug && sync_needed)
		(void) fprintf(stderr, "efi_use_whole_disk: sync needed\n");

	/*
	 * If alter_lba is 1, we are using the backup label.
	 * Since we can locate the backup label by disk capacity,
	 * there must be no unallocated space.
	 */
	if ((efi_label->efi_altern_lba == 1) || (efi_label->efi_altern_lba
	    >= efi_label->efi_last_lba && !sync_needed)) {
		if (efi_debug) {
			(void) fprintf(stderr,
			    "efi_use_whole_disk: requested space not found\n");
		}
		efi_free(efi_label);
		return (VT_ENOSPC);
	}

	/*
	 * Verify that we've found the reserved partition by checking
	 * that it looks the way it did when we created it in zpool_label_disk.
	 * If we've found the incorrect partition, then we know that this
	 * device was reformatted and no longer is solely used by ZFS.
	 */
	if ((efi_label->efi_parts[resv_index].p_size != EFI_MIN_RESV_SIZE) ||
	    (efi_label->efi_parts[resv_index].p_tag != V_RESERVED) ||
	    (resv_index != 8)) {
		if (efi_debug) {
			(void) fprintf(stderr,
			    "efi_use_whole_disk: wholedisk not available\n");
		}
		efi_free(efi_label);
		return (VT_ENOSPC);
	}

	if (data_start + data_size != resv_start) {
		if (efi_debug) {
			(void) fprintf(stderr,
			    "efi_use_whole_disk: "
			    "data_start (%lli) + "
			    "data_size (%lli) != "
			    "resv_start (%lli)\n",
			    data_start, data_size, resv_start);
		}

		return (VT_EINVAL);
	}

	if (limit < resv_start) {
		if (efi_debug) {
			(void) fprintf(stderr,
			    "efi_use_whole_disk: "
			    "limit (%lli) < resv_start (%lli)\n",
			    limit, resv_start);
		}

		return (VT_EINVAL);
	}

	difference = limit - resv_start;

	if (efi_debug)
		(void) fprintf(stderr,
		    "efi_use_whole_disk: difference is %lli\n", difference);

	/*
	 * Move the reserved partition. There is currently no data in
	 * here except fabricated devids (which get generated via
	 * efi_write()). So there is no need to copy data.
	 */
	efi_label->efi_parts[data_index].p_size += difference;
	efi_label->efi_parts[resv_index].p_start += difference;
	efi_label->efi_last_u_lba = efi_label->efi_last_lba - nblocks;

	rval = efi_write(fd, efi_label);
	if (rval < 0) {
		if (efi_debug) {
			(void) fprintf(stderr,
			    "efi_use_whole_disk:fail to write label, rval=%d\n",
			    rval);
		}
		efi_free(efi_label);
		return (rval);
	}

	efi_free(efi_label);
	return (0);
}