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
typedef  int namecheck_err_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  NAME_ERR_DISKLIKE 138 
#define  NAME_ERR_EMPTY_COMPONENT 137 
#define  NAME_ERR_INVALCHAR 136 
#define  NAME_ERR_LEADING_SLASH 135 
#define  NAME_ERR_MULTIPLE_DELIMITERS 134 
#define  NAME_ERR_NOLETTER 133 
#define  NAME_ERR_PARENT_REF 132 
#define  NAME_ERR_RESERVED 131 
#define  NAME_ERR_SELF_REF 130 
#define  NAME_ERR_TOOLONG 129 
#define  NAME_ERR_TRAILING_SLASH 128 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_TYPE_BOOKMARK ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ entity_namecheck (char const*,int*,char*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int
zfs_validate_name(libzfs_handle_t *hdl, const char *path, int type,
    boolean_t modifying)
{
	namecheck_err_t why;
	char what;

	if (!(type & ZFS_TYPE_SNAPSHOT) && strchr(path, '@') != NULL) {
		if (hdl != NULL)
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "snapshot delimiter '@' is not expected here"));
		return (0);
	}

	if (type == ZFS_TYPE_SNAPSHOT && strchr(path, '@') == NULL) {
		if (hdl != NULL)
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "missing '@' delimiter in snapshot name"));
		return (0);
	}

	if (!(type & ZFS_TYPE_BOOKMARK) && strchr(path, '#') != NULL) {
		if (hdl != NULL)
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "bookmark delimiter '#' is not expected here"));
		return (0);
	}

	if (type == ZFS_TYPE_BOOKMARK && strchr(path, '#') == NULL) {
		if (hdl != NULL)
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "missing '#' delimiter in bookmark name"));
		return (0);
	}

	if (modifying && strchr(path, '%') != NULL) {
		if (hdl != NULL)
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "invalid character %c in name"), '%');
		return (0);
	}

	if (entity_namecheck(path, &why, &what) != 0) {
		if (hdl != NULL) {
			switch (why) {
			case NAME_ERR_TOOLONG:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "name is too long"));
				break;

			case NAME_ERR_LEADING_SLASH:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "leading slash in name"));
				break;

			case NAME_ERR_EMPTY_COMPONENT:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "empty component or misplaced '@'"
				    " or '#' delimiter in name"));
				break;

			case NAME_ERR_TRAILING_SLASH:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "trailing slash in name"));
				break;

			case NAME_ERR_INVALCHAR:
				zfs_error_aux(hdl,
				    dgettext(TEXT_DOMAIN, "invalid character "
				    "'%c' in name"), what);
				break;

			case NAME_ERR_MULTIPLE_DELIMITERS:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "multiple '@' and/or '#' delimiters in "
				    "name"));
				break;

			case NAME_ERR_NOLETTER:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "pool doesn't begin with a letter"));
				break;

			case NAME_ERR_RESERVED:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "name is reserved"));
				break;

			case NAME_ERR_DISKLIKE:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "reserved disk name"));
				break;

			case NAME_ERR_SELF_REF:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "self reference, '.' is found in name"));
				break;

			case NAME_ERR_PARENT_REF:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "parent reference, '..' is found in name"));
				break;

			default:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "(%d) not defined"), why);
				break;
			}
		}

		return (0);
	}

	return (-1);
}