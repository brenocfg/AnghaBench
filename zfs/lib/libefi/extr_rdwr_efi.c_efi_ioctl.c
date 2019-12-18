#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_3__ {int dki_lba; int dki_length; void* dki_data; } ;
typedef  TYPE_1__ dk_efi_t ;
typedef  int /*<<< orphan*/  diskaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKFLSBUF ; 
 int DEV_BSIZE ; 
#define  DKIOCGETEFI 129 
#define  DKIOCSETEFI 128 
 int EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ efi_debug ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fsync (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,void*,int) ; 
 int read_disk_info (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,void*,int) ; 

__attribute__((used)) static int
efi_ioctl(int fd, int cmd, dk_efi_t *dk_ioc)
{
	void *data = dk_ioc->dki_data;
	int error;
	diskaddr_t capacity;
	uint_t lbsize;

	/*
	 * When the IO is not being performed in kernel as an ioctl we need
	 * to know the sector size so we can seek to the proper byte offset.
	 */
	if (read_disk_info(fd, &capacity, &lbsize) == -1) {
		if (efi_debug)
			fprintf(stderr, "unable to read disk info: %d", errno);

		errno = EIO;
		return (-1);
	}

	switch (cmd) {
	case DKIOCGETEFI:
		if (lbsize == 0) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCGETEFI assuming "
				    "LBA %d bytes\n", DEV_BSIZE);

			lbsize = DEV_BSIZE;
		}

		error = lseek(fd, dk_ioc->dki_lba * lbsize, SEEK_SET);
		if (error == -1) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCGETEFI lseek "
				    "error: %d\n", errno);
			return (error);
		}

		error = read(fd, data, dk_ioc->dki_length);
		if (error == -1) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCGETEFI read "
				    "error: %d\n", errno);
			return (error);
		}

		if (error != dk_ioc->dki_length) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCGETEFI short "
				    "read of %d bytes\n", error);
			errno = EIO;
			return (-1);
		}
		error = 0;
		break;

	case DKIOCSETEFI:
		if (lbsize == 0) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCSETEFI unknown "
				    "LBA size\n");
			errno = EIO;
			return (-1);
		}

		error = lseek(fd, dk_ioc->dki_lba * lbsize, SEEK_SET);
		if (error == -1) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCSETEFI lseek "
				    "error: %d\n", errno);
			return (error);
		}

		error = write(fd, data, dk_ioc->dki_length);
		if (error == -1) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCSETEFI write "
				    "error: %d\n", errno);
			return (error);
		}

		if (error != dk_ioc->dki_length) {
			if (efi_debug)
				(void) fprintf(stderr, "DKIOCSETEFI short "
				    "write of %d bytes\n", error);
			errno = EIO;
			return (-1);
		}

		/* Sync the new EFI table to disk */
		error = fsync(fd);
		if (error == -1)
			return (error);

		/* Ensure any local disk cache is also flushed */
		if (ioctl(fd, BLKFLSBUF, 0) == -1)
			return (error);

		error = 0;
		break;

	default:
		if (efi_debug)
			(void) fprintf(stderr, "unsupported ioctl()\n");

		errno = EIO;
		return (-1);
	}

	return (error);
}