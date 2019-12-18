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
#define  ZFS_DELEG_CREATE 137 
#define  ZFS_DELEG_CREATE_SETS 136 
 char ZFS_DELEG_DESCENDENT ; 
#define  ZFS_DELEG_EVERYONE 135 
#define  ZFS_DELEG_EVERYONE_SETS 134 
 char ZFS_DELEG_FIELD_SEP_CHR ; 
#define  ZFS_DELEG_GROUP 133 
#define  ZFS_DELEG_GROUP_SETS 132 
 char ZFS_DELEG_LOCAL ; 
 char ZFS_DELEG_NA ; 
#define  ZFS_DELEG_NAMED_SET 131 
#define  ZFS_DELEG_NAMED_SET_SETS 130 
#define  ZFS_DELEG_USER 129 
#define  ZFS_DELEG_USER_SETS 128 
 int /*<<< orphan*/  isdigit (char) ; 
 int permset_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_validate_who(char *who)
{
	char *p;

	if (who[2] != ZFS_DELEG_FIELD_SEP_CHR)
		return (-1);

	switch (who[0]) {
	case ZFS_DELEG_USER:
	case ZFS_DELEG_GROUP:
	case ZFS_DELEG_USER_SETS:
	case ZFS_DELEG_GROUP_SETS:
		if (who[1] != ZFS_DELEG_LOCAL && who[1] != ZFS_DELEG_DESCENDENT)
			return (-1);
		for (p = &who[3]; *p; p++)
			if (!isdigit(*p))
				return (-1);
		break;

	case ZFS_DELEG_NAMED_SET:
	case ZFS_DELEG_NAMED_SET_SETS:
		if (who[1] != ZFS_DELEG_NA)
			return (-1);
		return (permset_namecheck(&who[3], NULL, NULL));

	case ZFS_DELEG_CREATE:
	case ZFS_DELEG_CREATE_SETS:
		if (who[1] != ZFS_DELEG_NA)
			return (-1);
		if (who[3] != '\0')
			return (-1);
		break;

	case ZFS_DELEG_EVERYONE:
	case ZFS_DELEG_EVERYONE_SETS:
		if (who[1] != ZFS_DELEG_LOCAL && who[1] != ZFS_DELEG_DESCENDENT)
			return (-1);
		if (who[3] != '\0')
			return (-1);
		break;

	default:
		return (-1);
	}

	return (0);
}