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
struct dk_gpt {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EFI_NUMPAR ; 
 int O_DIRECT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ efi_alloc_and_init (int,int /*<<< orphan*/ ,struct dk_gpt**) ; 
 int /*<<< orphan*/  efi_free (struct dk_gpt*) ; 
 int open (char const*,int) ; 

boolean_t
zfs_dev_is_whole_disk(const char *dev_name)
{
	struct dk_gpt *label;
	int fd;

	if ((fd = open(dev_name, O_RDONLY | O_DIRECT)) < 0)
		return (B_FALSE);

	if (efi_alloc_and_init(fd, EFI_NUMPAR, &label) != 0) {
		(void) close(fd);
		return (B_FALSE);
	}

	efi_free(label);
	(void) close(fd);

	return (B_TRUE);
}