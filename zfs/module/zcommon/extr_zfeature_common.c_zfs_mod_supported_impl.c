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
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int asprintf (char**,char*,char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 

__attribute__((used)) static boolean_t
zfs_mod_supported_impl(const char *scope, const char *name, const char *sysfs)
{
	boolean_t supported = B_FALSE;
	char *path;

	int len = asprintf(&path, "%s%s%s%s%s", sysfs,
	    scope == NULL ? "" : "/", scope == NULL ? "" : scope,
	    name == NULL ? "" : "/", name == NULL ? "" : name);
	if (len > 0) {
		struct stat64 statbuf;
		supported = !!(stat64(path, &statbuf) == 0);
		free(path);
	}

	return (supported);
}