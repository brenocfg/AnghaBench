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
typedef  int /*<<< orphan*/  zver_userland ;
typedef  int /*<<< orphan*/  zver_kernel ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int zfs_version_kernel (char*,int) ; 
 int /*<<< orphan*/  zfs_version_userland (char*,int) ; 

int
zfs_version_print(void)
{
	char zver_userland[128];
	char zver_kernel[128];

	if (zfs_version_kernel(zver_kernel, sizeof (zver_kernel)) == -1) {
		fprintf(stderr, "zfs_version_kernel() failed: %s\n",
		    strerror(errno));
		return (-1);
	}

	zfs_version_userland(zver_userland, sizeof (zver_userland));

	(void) printf("%s\n", zver_userland);
	(void) printf("zfs-kmod-%s\n", zver_kernel);

	return (0);
}