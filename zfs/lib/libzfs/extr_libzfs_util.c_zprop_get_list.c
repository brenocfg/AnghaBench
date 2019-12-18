#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* pl_next; } ;
typedef  TYPE_1__ zprop_list_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ addlist (int /*<<< orphan*/ *,char*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zprop_get_list(libzfs_handle_t *hdl, char *props, zprop_list_t **listp,
    zfs_type_t type)
{
	*listp = NULL;

	/*
	 * If 'all' is specified, return a NULL list.
	 */
	if (strcmp(props, "all") == 0)
		return (0);

	/*
	 * If no props were specified, return an error.
	 */
	if (props[0] == '\0') {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "no properties specified"));
		return (zfs_error(hdl, EZFS_BADPROP, dgettext(TEXT_DOMAIN,
		    "bad property list")));
	}

	/*
	 * It would be nice to use getsubopt() here, but the inclusion of column
	 * aliases makes this more effort than it's worth.
	 */
	while (*props != '\0') {
		size_t len;
		char *p;
		char c;

		if ((p = strchr(props, ',')) == NULL) {
			len = strlen(props);
			p = props + len;
		} else {
			len = p - props;
		}

		/*
		 * Check for empty options.
		 */
		if (len == 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "empty property name"));
			return (zfs_error(hdl, EZFS_BADPROP,
			    dgettext(TEXT_DOMAIN, "bad property list")));
		}

		/*
		 * Check all regular property names.
		 */
		c = props[len];
		props[len] = '\0';

		if (strcmp(props, "space") == 0) {
			static char *spaceprops[] = {
				"name", "avail", "used", "usedbysnapshots",
				"usedbydataset", "usedbyrefreservation",
				"usedbychildren", NULL
			};
			int i;

			for (i = 0; spaceprops[i]; i++) {
				if (addlist(hdl, spaceprops[i], listp, type))
					return (-1);
				listp = &(*listp)->pl_next;
			}
		} else {
			if (addlist(hdl, props, listp, type))
				return (-1);
			listp = &(*listp)->pl_next;
		}

		props = p;
		if (c == ',')
			props++;
	}

	return (0);
}