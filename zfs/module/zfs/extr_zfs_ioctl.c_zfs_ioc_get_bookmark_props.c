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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fsname ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_get_bookmark_props (char*,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int
zfs_ioc_get_bookmark_props(const char *bookmark, nvlist_t *innvl,
    nvlist_t *outnvl)
{
	char fsname[ZFS_MAX_DATASET_NAME_LEN];
	char *bmname;

	bmname = strchr(bookmark, '#');
	if (bmname == NULL)
		return (SET_ERROR(EINVAL));
	bmname++;

	(void) strlcpy(fsname, bookmark, sizeof (fsname));
	*(strchr(fsname, '#')) = '\0';

	return (dsl_get_bookmark_props(fsname, bmname, outnvl));
}