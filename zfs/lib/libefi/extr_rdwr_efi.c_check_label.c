#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int len_t ;
struct TYPE_5__ {scalar_t__ efi_gpt_Signature; int efi_gpt_HeaderCRC32; int /*<<< orphan*/  efi_gpt_HeaderSize; } ;
typedef  TYPE_1__ efi_gpt_t ;
struct TYPE_6__ {int dki_length; TYPE_1__* dki_data; } ;
typedef  TYPE_2__ dk_efi_t ;

/* Variables and functions */
 int /*<<< orphan*/  DKIOCGETEFI ; 
 int EFI_LABEL_SIZE ; 
 int EFI_MIN_LABEL_SIZE ; 
 int /*<<< orphan*/  EFI_SIGNATURE ; 
#define  EIO 128 
 int LE_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ LE_64 (int /*<<< orphan*/ ) ; 
 int VT_EINVAL ; 
 int VT_EIO ; 
 int VT_ERROR ; 
 int /*<<< orphan*/  efi_crc32 (unsigned char*,int) ; 
 scalar_t__ efi_debug ; 
 int efi_ioctl (int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
check_label(int fd, dk_efi_t *dk_ioc)
{
	efi_gpt_t		*efi;
	uint_t			crc;

	if (efi_ioctl(fd, DKIOCGETEFI, dk_ioc) == -1) {
		switch (errno) {
		case EIO:
			return (VT_EIO);
		default:
			return (VT_ERROR);
		}
	}
	efi = dk_ioc->dki_data;
	if (efi->efi_gpt_Signature != LE_64(EFI_SIGNATURE)) {
		if (efi_debug)
			(void) fprintf(stderr,
			    "Bad EFI signature: 0x%llx != 0x%llx\n",
			    (long long)efi->efi_gpt_Signature,
			    (long long)LE_64(EFI_SIGNATURE));
		return (VT_EINVAL);
	}

	/*
	 * check CRC of the header; the size of the header should
	 * never be larger than one block
	 */
	crc = efi->efi_gpt_HeaderCRC32;
	efi->efi_gpt_HeaderCRC32 = 0;
	len_t headerSize = (len_t)LE_32(efi->efi_gpt_HeaderSize);

	if (headerSize < EFI_MIN_LABEL_SIZE || headerSize > EFI_LABEL_SIZE) {
		if (efi_debug)
			(void) fprintf(stderr,
			    "Invalid EFI HeaderSize %llu.  Assuming %d.\n",
			    headerSize, EFI_MIN_LABEL_SIZE);
	}

	if ((headerSize > dk_ioc->dki_length) ||
	    crc != LE_32(efi_crc32((unsigned char *)efi, headerSize))) {
		if (efi_debug)
			(void) fprintf(stderr,
			    "Bad EFI CRC: 0x%x != 0x%x\n",
			    crc, LE_32(efi_crc32((unsigned char *)efi,
			    headerSize)));
		return (VT_EINVAL);
	}

	return (0);
}