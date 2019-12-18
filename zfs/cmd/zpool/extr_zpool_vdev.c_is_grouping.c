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
 int INT_MAX ; 
 char* VDEV_ALLOC_BIAS_DEDUP ; 
 char* VDEV_ALLOC_BIAS_SPECIAL ; 
 char const* VDEV_TYPE_L2CACHE ; 
 char const* VDEV_TYPE_LOG ; 
 char const* VDEV_TYPE_MIRROR ; 
 char const* VDEV_TYPE_RAIDZ ; 
 char const* VDEV_TYPE_SPARE ; 
 scalar_t__ errno ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static const char *
is_grouping(const char *type, int *mindev, int *maxdev)
{
	if (strncmp(type, "raidz", 5) == 0) {
		const char *p = type + 5;
		char *end;
		long nparity;

		if (*p == '\0') {
			nparity = 1;
		} else if (*p == '0') {
			return (NULL); /* no zero prefixes allowed */
		} else {
			errno = 0;
			nparity = strtol(p, &end, 10);
			if (errno != 0 || nparity < 1 || nparity >= 255 ||
			    *end != '\0')
				return (NULL);
		}

		if (mindev != NULL)
			*mindev = nparity + 1;
		if (maxdev != NULL)
			*maxdev = 255;
		return (VDEV_TYPE_RAIDZ);
	}

	if (maxdev != NULL)
		*maxdev = INT_MAX;

	if (strcmp(type, "mirror") == 0) {
		if (mindev != NULL)
			*mindev = 2;
		return (VDEV_TYPE_MIRROR);
	}

	if (strcmp(type, "spare") == 0) {
		if (mindev != NULL)
			*mindev = 1;
		return (VDEV_TYPE_SPARE);
	}

	if (strcmp(type, "log") == 0) {
		if (mindev != NULL)
			*mindev = 1;
		return (VDEV_TYPE_LOG);
	}

	if (strcmp(type, VDEV_ALLOC_BIAS_SPECIAL) == 0 ||
	    strcmp(type, VDEV_ALLOC_BIAS_DEDUP) == 0) {
		if (mindev != NULL)
			*mindev = 1;
		return (type);
	}

	if (strcmp(type, "cache") == 0) {
		if (mindev != NULL)
			*mindev = 1;
		return (VDEV_TYPE_L2CACHE);
	}

	return (NULL);
}