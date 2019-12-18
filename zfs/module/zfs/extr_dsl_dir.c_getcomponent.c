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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strpbrk (char const*,char*) ; 

__attribute__((used)) static int
getcomponent(const char *path, char *component, const char **nextp)
{
	char *p;

	if ((path == NULL) || (path[0] == '\0'))
		return (SET_ERROR(ENOENT));
	/* This would be a good place to reserve some namespace... */
	p = strpbrk(path, "/@");
	if (p && (p[1] == '/' || p[1] == '@')) {
		/* two separators in a row */
		return (SET_ERROR(EINVAL));
	}
	if (p == NULL || p == path) {
		/*
		 * if the first thing is an @ or /, it had better be an
		 * @ and it had better not have any more ats or slashes,
		 * and it had better have something after the @.
		 */
		if (p != NULL &&
		    (p[0] != '@' || strpbrk(path+1, "/@") || p[1] == '\0'))
			return (SET_ERROR(EINVAL));
		if (strlen(path) >= ZFS_MAX_DATASET_NAME_LEN)
			return (SET_ERROR(ENAMETOOLONG));
		(void) strcpy(component, path);
		p = NULL;
	} else if (p[0] == '/') {
		if (p - path >= ZFS_MAX_DATASET_NAME_LEN)
			return (SET_ERROR(ENAMETOOLONG));
		(void) strncpy(component, path, p - path);
		component[p - path] = '\0';
		p++;
	} else if (p[0] == '@') {
		/*
		 * if the next separator is an @, there better not be
		 * any more slashes.
		 */
		if (strchr(path, '/'))
			return (SET_ERROR(EINVAL));
		if (p - path >= ZFS_MAX_DATASET_NAME_LEN)
			return (SET_ERROR(ENAMETOOLONG));
		(void) strncpy(component, path, p - path);
		component[p - path] = '\0';
	} else {
		panic("invalid p=%p", (void *)p);
	}
	*nextp = p;
	return (0);
}