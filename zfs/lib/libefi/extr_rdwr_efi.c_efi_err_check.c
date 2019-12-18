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
struct dk_gpt {int efi_nparts; int efi_first_u_lba; int efi_last_u_lba; TYPE_1__* efi_parts; } ;
typedef  int diskaddr_t ;
struct TYPE_2__ {scalar_t__ p_tag; int p_size; int p_start; } ;

/* Variables and functions */
 int EFI_MIN_RESV_SIZE ; 
 scalar_t__ V_RESERVED ; 
 scalar_t__ V_UNASSIGNED ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
efi_err_check(struct dk_gpt *vtoc)
{
	int			resv_part = -1;
	int			i, j;
	diskaddr_t		istart, jstart, isize, jsize, endsect;
	int			overlap = 0;

	/*
	 * make sure no partitions overlap
	 */
	for (i = 0; i < vtoc->efi_nparts; i++) {
		/* It can't be unassigned and have an actual size */
		if ((vtoc->efi_parts[i].p_tag == V_UNASSIGNED) &&
		    (vtoc->efi_parts[i].p_size != 0)) {
			(void) fprintf(stderr,
			    "partition %d is \"unassigned\" but has a size "
			    "of %llu\n", i, vtoc->efi_parts[i].p_size);
		}
		if (vtoc->efi_parts[i].p_tag == V_UNASSIGNED) {
			continue;
		}
		if (vtoc->efi_parts[i].p_tag == V_RESERVED) {
			if (resv_part != -1) {
				(void) fprintf(stderr,
				    "found duplicate reserved partition at "
				    "%d\n", i);
			}
			resv_part = i;
			if (vtoc->efi_parts[i].p_size != EFI_MIN_RESV_SIZE)
				(void) fprintf(stderr,
				    "Warning: reserved partition size must "
				    "be %d sectors\n", EFI_MIN_RESV_SIZE);
		}
		if ((vtoc->efi_parts[i].p_start < vtoc->efi_first_u_lba) ||
		    (vtoc->efi_parts[i].p_start > vtoc->efi_last_u_lba)) {
			(void) fprintf(stderr,
			    "Partition %d starts at %llu\n",
			    i,
			    vtoc->efi_parts[i].p_start);
			(void) fprintf(stderr,
			    "It must be between %llu and %llu.\n",
			    vtoc->efi_first_u_lba,
			    vtoc->efi_last_u_lba);
		}
		if ((vtoc->efi_parts[i].p_start +
		    vtoc->efi_parts[i].p_size <
		    vtoc->efi_first_u_lba) ||
		    (vtoc->efi_parts[i].p_start +
		    vtoc->efi_parts[i].p_size >
		    vtoc->efi_last_u_lba + 1)) {
			(void) fprintf(stderr,
			    "Partition %d ends at %llu\n",
			    i,
			    vtoc->efi_parts[i].p_start +
			    vtoc->efi_parts[i].p_size);
			(void) fprintf(stderr,
			    "It must be between %llu and %llu.\n",
			    vtoc->efi_first_u_lba,
			    vtoc->efi_last_u_lba);
		}

		for (j = 0; j < vtoc->efi_nparts; j++) {
			isize = vtoc->efi_parts[i].p_size;
			jsize = vtoc->efi_parts[j].p_size;
			istart = vtoc->efi_parts[i].p_start;
			jstart = vtoc->efi_parts[j].p_start;
			if ((i != j) && (isize != 0) && (jsize != 0)) {
				endsect = jstart + jsize -1;
				if ((jstart <= istart) &&
				    (istart <= endsect)) {
					if (!overlap) {
					(void) fprintf(stderr,
					    "label error: EFI Labels do not "
					    "support overlapping partitions\n");
					}
					(void) fprintf(stderr,
					    "Partition %d overlaps partition "
					    "%d.\n", i, j);
					overlap = 1;
				}
			}
		}
	}
	/* make sure there is a reserved partition */
	if (resv_part == -1) {
		(void) fprintf(stderr,
		    "no reserved partition found\n");
	}
}