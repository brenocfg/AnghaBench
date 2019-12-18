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
typedef  int /*<<< orphan*/  uchar_t ;
struct dk_gpt {int efi_nparts; int efi_first_u_lba; int efi_last_u_lba; TYPE_1__* efi_parts; } ;
typedef  int diskaddr_t ;
struct TYPE_2__ {int p_tag; int p_size; int p_start; int /*<<< orphan*/  p_guid; } ;

/* Variables and functions */
 int VT_EINVAL ; 
 int V_RESERVED ; 
 int V_UNASSIGNED ; 
 scalar_t__ efi_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_input(struct dk_gpt *vtoc)
{
	int			resv_part = -1;
	int			i, j;
	diskaddr_t		istart, jstart, isize, jsize, endsect;

	/*
	 * Sanity-check the input (make sure no partitions overlap)
	 */
	for (i = 0; i < vtoc->efi_nparts; i++) {
		/* It can't be unassigned and have an actual size */
		if ((vtoc->efi_parts[i].p_tag == V_UNASSIGNED) &&
		    (vtoc->efi_parts[i].p_size != 0)) {
			if (efi_debug) {
				(void) fprintf(stderr, "partition %d is "
				    "\"unassigned\" but has a size of %llu",
				    i, vtoc->efi_parts[i].p_size);
			}
			return (VT_EINVAL);
		}
		if (vtoc->efi_parts[i].p_tag == V_UNASSIGNED) {
			if (uuid_is_null((uchar_t *)&vtoc->efi_parts[i].p_guid))
				continue;
			/* we have encountered an unknown uuid */
			vtoc->efi_parts[i].p_tag = 0xff;
		}
		if (vtoc->efi_parts[i].p_tag == V_RESERVED) {
			if (resv_part != -1) {
				if (efi_debug) {
					(void) fprintf(stderr, "found "
					    "duplicate reserved partition "
					    "at %d\n", i);
				}
				return (VT_EINVAL);
			}
			resv_part = i;
		}
		if ((vtoc->efi_parts[i].p_start < vtoc->efi_first_u_lba) ||
		    (vtoc->efi_parts[i].p_start > vtoc->efi_last_u_lba)) {
			if (efi_debug) {
				(void) fprintf(stderr,
				    "Partition %d starts at %llu.  ",
				    i,
				    vtoc->efi_parts[i].p_start);
				(void) fprintf(stderr,
				    "It must be between %llu and %llu.\n",
				    vtoc->efi_first_u_lba,
				    vtoc->efi_last_u_lba);
			}
			return (VT_EINVAL);
		}
		if ((vtoc->efi_parts[i].p_start +
		    vtoc->efi_parts[i].p_size <
		    vtoc->efi_first_u_lba) ||
		    (vtoc->efi_parts[i].p_start +
		    vtoc->efi_parts[i].p_size >
		    vtoc->efi_last_u_lba + 1)) {
			if (efi_debug) {
				(void) fprintf(stderr,
				    "Partition %d ends at %llu.  ",
				    i,
				    vtoc->efi_parts[i].p_start +
				    vtoc->efi_parts[i].p_size);
				(void) fprintf(stderr,
				    "It must be between %llu and %llu.\n",
				    vtoc->efi_first_u_lba,
				    vtoc->efi_last_u_lba);
			}
			return (VT_EINVAL);
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
					if (efi_debug) {
						(void) fprintf(stderr,
						    "Partition %d overlaps "
						    "partition %d.", i, j);
					}
					return (VT_EINVAL);
				}
			}
		}
	}
	/* just a warning for now */
	if ((resv_part == -1) && efi_debug) {
		(void) fprintf(stderr,
		    "no reserved partition found\n");
	}
	return (0);
}