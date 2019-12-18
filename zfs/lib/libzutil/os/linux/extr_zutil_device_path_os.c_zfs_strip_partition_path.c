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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 
 char* zfs_strip_partition (char*) ; 

__attribute__((used)) static char *
zfs_strip_partition_path(char *path)
{
	char *newpath = strdup(path);
	char *sd_offset;
	char *new_sd;

	if (!newpath)
		return (NULL);

	/* Point to "sda1" part of "/dev/sda1" */
	sd_offset = strrchr(newpath, '/') + 1;

	/* Get our new name "sda" */
	new_sd = zfs_strip_partition(sd_offset);
	if (!new_sd) {
		free(newpath);
		return (NULL);
	}

	/* Paste the "sda" where "sda1" was */
	strlcpy(sd_offset, new_sd, strlen(sd_offset) + 1);

	/* Free temporary "sda" */
	free(new_sd);

	return (newpath);
}