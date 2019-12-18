#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zpool_start_block; int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_2__ zpool_handle_t ;
typedef  scalar_t__ uint64_t ;
struct dk_gpt {scalar_t__ efi_last_u_lba; TYPE_1__* efi_parts; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  scalar_t__ diskaddr_t ;
struct TYPE_4__ {size_t p_size; int /*<<< orphan*/  p_tag; scalar_t__ p_start; int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKFLSBUF ; 
 int /*<<< orphan*/  DISK_LABEL_WAIT ; 
 char* DISK_ROOT ; 
 size_t EFI_MIN_RESV_SIZE ; 
 int /*<<< orphan*/  EFI_NUMPAR ; 
 int /*<<< orphan*/  EFI_PART_NAME_LEN ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EZFS_LABELFAILED ; 
 int /*<<< orphan*/  EZFS_NOCAP ; 
 int /*<<< orphan*/  EZFS_OPENFAILED ; 
 scalar_t__ MAXOFFSET_T ; 
 int MAXPATHLEN ; 
 scalar_t__ NEW_START_BLOCK ; 
 int O_DIRECT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ P2ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARTITION_END_ALIGNMENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  V_RESERVED ; 
 int /*<<< orphan*/  V_USR ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  close (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ efi_alloc_and_init (int,int /*<<< orphan*/ ,struct dk_gpt**) ; 
 int /*<<< orphan*/  efi_free (struct dk_gpt*) ; 
 int efi_rescan (int) ; 
 int efi_write (int,struct dk_gpt*) ; 
 scalar_t__ errno ; 
 scalar_t__ find_start_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_append_partition (char*,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zpool_label_disk_check (char*) ; 
 int zpool_label_disk_wait (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_label_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zpool_label_disk(libzfs_handle_t *hdl, zpool_handle_t *zhp, char *name)
{
	char path[MAXPATHLEN];
	struct dk_gpt *vtoc;
	int rval, fd;
	size_t resv = EFI_MIN_RESV_SIZE;
	uint64_t slice_size;
	diskaddr_t start_block;
	char errbuf[1024];

	/* prepare an error message just in case */
	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot label '%s'"), name);

	if (zhp) {
		nvlist_t *nvroot;

		verify(nvlist_lookup_nvlist(zhp->zpool_config,
		    ZPOOL_CONFIG_VDEV_TREE, &nvroot) == 0);

		if (zhp->zpool_start_block == 0)
			start_block = find_start_block(nvroot);
		else
			start_block = zhp->zpool_start_block;
		zhp->zpool_start_block = start_block;
	} else {
		/* new pool */
		start_block = NEW_START_BLOCK;
	}

	(void) snprintf(path, sizeof (path), "%s/%s", DISK_ROOT, name);

	if ((fd = open(path, O_RDWR|O_DIRECT|O_EXCL)) < 0) {
		/*
		 * This shouldn't happen.  We've long since verified that this
		 * is a valid device.
		 */
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "cannot "
		    "label '%s': unable to open device: %d"), path, errno);
		return (zfs_error(hdl, EZFS_OPENFAILED, errbuf));
	}

	if (efi_alloc_and_init(fd, EFI_NUMPAR, &vtoc) != 0) {
		/*
		 * The only way this can fail is if we run out of memory, or we
		 * were unable to read the disk's capacity
		 */
		if (errno == ENOMEM)
			(void) no_memory(hdl);

		(void) close(fd);
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "cannot "
		    "label '%s': unable to read disk capacity"), path);

		return (zfs_error(hdl, EZFS_NOCAP, errbuf));
	}

	slice_size = vtoc->efi_last_u_lba + 1;
	slice_size -= EFI_MIN_RESV_SIZE;
	if (start_block == MAXOFFSET_T)
		start_block = NEW_START_BLOCK;
	slice_size -= start_block;
	slice_size = P2ALIGN(slice_size, PARTITION_END_ALIGNMENT);

	vtoc->efi_parts[0].p_start = start_block;
	vtoc->efi_parts[0].p_size = slice_size;

	/*
	 * Why we use V_USR: V_BACKUP confuses users, and is considered
	 * disposable by some EFI utilities (since EFI doesn't have a backup
	 * slice).  V_UNASSIGNED is supposed to be used only for zero size
	 * partitions, and efi_write() will fail if we use it.  V_ROOT, V_BOOT,
	 * etc. were all pretty specific.  V_USR is as close to reality as we
	 * can get, in the absence of V_OTHER.
	 */
	vtoc->efi_parts[0].p_tag = V_USR;
	zpool_label_name(vtoc->efi_parts[0].p_name, EFI_PART_NAME_LEN);

	vtoc->efi_parts[8].p_start = slice_size + start_block;
	vtoc->efi_parts[8].p_size = resv;
	vtoc->efi_parts[8].p_tag = V_RESERVED;

	rval = efi_write(fd, vtoc);

	/* Flush the buffers to disk and invalidate the page cache. */
	(void) fsync(fd);
	(void) ioctl(fd, BLKFLSBUF);

	if (rval == 0)
		rval = efi_rescan(fd);

	/*
	 * Some block drivers (like pcata) may not support EFI GPT labels.
	 * Print out a helpful error message directing the user to manually
	 * label the disk and give a specific slice.
	 */
	if (rval != 0) {
		(void) close(fd);
		efi_free(vtoc);

		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "try using "
		    "parted(8) and then provide a specific slice: %d"), rval);
		return (zfs_error(hdl, EZFS_LABELFAILED, errbuf));
	}

	(void) close(fd);
	efi_free(vtoc);

	(void) snprintf(path, sizeof (path), "%s/%s", DISK_ROOT, name);
	(void) zfs_append_partition(path, MAXPATHLEN);

	/* Wait to udev to signal use the device has settled. */
	rval = zpool_label_disk_wait(path, DISK_LABEL_WAIT);
	if (rval) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "failed to "
		    "detect device partitions on '%s': %d"), path, rval);
		return (zfs_error(hdl, EZFS_LABELFAILED, errbuf));
	}

	/* We can't be to paranoid.  Read the label back and verify it. */
	(void) snprintf(path, sizeof (path), "%s/%s", DISK_ROOT, name);
	rval = zpool_label_disk_check(path);
	if (rval) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "freshly written "
		    "EFI label on '%s' is damaged.  Ensure\nthis device "
		    "is not in use, and is functioning properly: %d"),
		    path, rval);
		return (zfs_error(hdl, EZFS_LABELFAILED, errbuf));
	}
	return (0);
}