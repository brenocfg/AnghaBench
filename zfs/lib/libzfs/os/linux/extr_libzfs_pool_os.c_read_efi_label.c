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
struct dk_gpt {TYPE_1__* efi_parts; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  diskname ;
typedef  int /*<<< orphan*/  diskaddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_start; } ;

/* Variables and functions */
 char* DISK_ROOT ; 
 int MAXPATHLEN ; 
 int O_DIRECT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  close (int) ; 
 int efi_alloc_and_read (int,struct dk_gpt**) ; 
 int /*<<< orphan*/  efi_free (struct dk_gpt*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strrchr (char*,char) ; 

__attribute__((used)) static int
read_efi_label(nvlist_t *config, diskaddr_t *sb)
{
	char *path;
	int fd;
	char diskname[MAXPATHLEN];
	int err = -1;

	if (nvlist_lookup_string(config, ZPOOL_CONFIG_PATH, &path) != 0)
		return (err);

	(void) snprintf(diskname, sizeof (diskname), "%s%s", DISK_ROOT,
	    strrchr(path, '/'));
	if ((fd = open(diskname, O_RDONLY|O_DIRECT)) >= 0) {
		struct dk_gpt *vtoc;

		if ((err = efi_alloc_and_read(fd, &vtoc)) >= 0) {
			if (sb != NULL)
				*sb = vtoc->efi_parts[0].p_start;
			efi_free(vtoc);
		}
		(void) close(fd);
	}
	return (err);
}