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
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkid_cache ;

/* Variables and functions */
 int blkid_get_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkid_put_cache (int /*<<< orphan*/ ) ; 
 int check_disk (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
check_device(const char *path, boolean_t force,
    boolean_t isspare, boolean_t iswholedisk)
{
	blkid_cache cache;
	int error;

	error = blkid_get_cache(&cache, NULL);
	if (error != 0) {
		(void) fprintf(stderr, gettext("unable to access the blkid "
		    "cache.\n"));
		return (-1);
	}

	error = check_disk(path, cache, force, isspare, iswholedisk);
	blkid_put_cache(cache);

	return (error);
}