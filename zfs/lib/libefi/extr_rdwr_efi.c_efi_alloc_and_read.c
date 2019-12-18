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
typedef  int uint32_t ;
struct dk_part {int dummy; } ;
struct dk_gpt {int efi_nparts; } ;
typedef  int /*<<< orphan*/  efi_gpe_t ;

/* Variables and functions */
 int EFI_MIN_ARRAY_SIZE ; 
 int VT_EINVAL ; 
 int VT_ERROR ; 
 struct dk_gpt* calloc (int,int) ; 
 scalar_t__ efi_debug ; 
 int efi_read (int,struct dk_gpt*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct dk_gpt*) ; 
 void* realloc (struct dk_gpt*,int) ; 
 int /*<<< orphan*/  stderr ; 

int
efi_alloc_and_read(int fd, struct dk_gpt **vtoc)
{
	int			rval;
	uint32_t		nparts;
	int			length;

	/* figure out the number of entries that would fit into 16K */
	nparts = EFI_MIN_ARRAY_SIZE / sizeof (efi_gpe_t);
	length = (int) sizeof (struct dk_gpt) +
	    (int) sizeof (struct dk_part) * (nparts - 1);
	if ((*vtoc = calloc(1, length)) == NULL)
		return (VT_ERROR);

	(*vtoc)->efi_nparts = nparts;
	rval = efi_read(fd, *vtoc);

	if ((rval == VT_EINVAL) && (*vtoc)->efi_nparts > nparts) {
		void *tmp;
		length = (int) sizeof (struct dk_gpt) +
		    (int) sizeof (struct dk_part) *
		    ((*vtoc)->efi_nparts - 1);
		nparts = (*vtoc)->efi_nparts;
		if ((tmp = realloc(*vtoc, length)) == NULL) {
			free (*vtoc);
			*vtoc = NULL;
			return (VT_ERROR);
		} else {
			*vtoc = tmp;
			rval = efi_read(fd, *vtoc);
		}
	}

	if (rval < 0) {
		if (efi_debug) {
			(void) fprintf(stderr,
			    "read of EFI table failed, rval=%d\n", rval);
		}
		free (*vtoc);
		*vtoc = NULL;
	}

	return (rval);
}