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
typedef  int zfs_deleg_note_t ;

/* Variables and functions */
#define  ZFS_DELEG_NOTE_GROUPOBJQUOTA 140 
#define  ZFS_DELEG_NOTE_GROUPOBJUSED 139 
#define  ZFS_DELEG_NOTE_GROUPQUOTA 138 
#define  ZFS_DELEG_NOTE_GROUPUSED 137 
#define  ZFS_DELEG_NOTE_PROJECTOBJQUOTA 136 
#define  ZFS_DELEG_NOTE_PROJECTOBJUSED 135 
#define  ZFS_DELEG_NOTE_PROJECTQUOTA 134 
#define  ZFS_DELEG_NOTE_PROJECTUSED 133 
#define  ZFS_DELEG_NOTE_USEROBJQUOTA 132 
#define  ZFS_DELEG_NOTE_USEROBJUSED 131 
#define  ZFS_DELEG_NOTE_USERPROP 130 
#define  ZFS_DELEG_NOTE_USERQUOTA 129 
#define  ZFS_DELEG_NOTE_USERUSED 128 
 char const* gettext (char*) ; 

__attribute__((used)) static inline const char *
deleg_perm_type(zfs_deleg_note_t note)
{
	/* subcommands */
	switch (note) {
		/* SUBCOMMANDS */
		/* OTHER */
	case ZFS_DELEG_NOTE_GROUPQUOTA:
	case ZFS_DELEG_NOTE_GROUPUSED:
	case ZFS_DELEG_NOTE_USERPROP:
	case ZFS_DELEG_NOTE_USERQUOTA:
	case ZFS_DELEG_NOTE_USERUSED:
	case ZFS_DELEG_NOTE_USEROBJQUOTA:
	case ZFS_DELEG_NOTE_USEROBJUSED:
	case ZFS_DELEG_NOTE_GROUPOBJQUOTA:
	case ZFS_DELEG_NOTE_GROUPOBJUSED:
	case ZFS_DELEG_NOTE_PROJECTUSED:
	case ZFS_DELEG_NOTE_PROJECTQUOTA:
	case ZFS_DELEG_NOTE_PROJECTOBJUSED:
	case ZFS_DELEG_NOTE_PROJECTOBJQUOTA:
		/* other */
		return (gettext("other"));
	default:
		return (gettext("subcommand"));
	}
}