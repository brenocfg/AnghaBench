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
struct stat64 {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  memset (struct stat64*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 scalar_t__ zfs_dev_is_whole_disk (char*) ; 
 int zfs_resolve_shortname (char const*,char*,size_t) ; 

__attribute__((used)) static int
is_shorthand_path(const char *arg, char *path, size_t path_size,
    struct stat64 *statbuf, boolean_t *wholedisk)
{
	int error;

	error = zfs_resolve_shortname(arg, path, path_size);
	if (error == 0) {
		*wholedisk = zfs_dev_is_whole_disk(path);
		if (*wholedisk || (stat64(path, statbuf) == 0))
			return (0);
	}

	strlcpy(path, arg, path_size);
	memset(statbuf, 0, sizeof (*statbuf));
	*wholedisk = B_FALSE;

	return (error);
}