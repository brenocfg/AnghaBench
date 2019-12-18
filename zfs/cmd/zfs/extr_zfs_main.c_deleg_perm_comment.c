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
#define  ZFS_DELEG_NOTE_ALLOW 157 
#define  ZFS_DELEG_NOTE_CHANGE_KEY 156 
#define  ZFS_DELEG_NOTE_CLONE 155 
#define  ZFS_DELEG_NOTE_CREATE 154 
#define  ZFS_DELEG_NOTE_DESTROY 153 
#define  ZFS_DELEG_NOTE_DIFF 152 
#define  ZFS_DELEG_NOTE_GROUPOBJQUOTA 151 
#define  ZFS_DELEG_NOTE_GROUPOBJUSED 150 
#define  ZFS_DELEG_NOTE_GROUPQUOTA 149 
#define  ZFS_DELEG_NOTE_GROUPUSED 148 
#define  ZFS_DELEG_NOTE_HOLD 147 
#define  ZFS_DELEG_NOTE_LOAD_KEY 146 
#define  ZFS_DELEG_NOTE_MOUNT 145 
#define  ZFS_DELEG_NOTE_PROJECTOBJQUOTA 144 
#define  ZFS_DELEG_NOTE_PROJECTOBJUSED 143 
#define  ZFS_DELEG_NOTE_PROJECTQUOTA 142 
#define  ZFS_DELEG_NOTE_PROJECTUSED 141 
#define  ZFS_DELEG_NOTE_PROMOTE 140 
#define  ZFS_DELEG_NOTE_RECEIVE 139 
#define  ZFS_DELEG_NOTE_RELEASE 138 
#define  ZFS_DELEG_NOTE_RENAME 137 
#define  ZFS_DELEG_NOTE_ROLLBACK 136 
#define  ZFS_DELEG_NOTE_SEND 135 
#define  ZFS_DELEG_NOTE_SHARE 134 
#define  ZFS_DELEG_NOTE_SNAPSHOT 133 
#define  ZFS_DELEG_NOTE_USEROBJQUOTA 132 
#define  ZFS_DELEG_NOTE_USEROBJUSED 131 
#define  ZFS_DELEG_NOTE_USERPROP 130 
#define  ZFS_DELEG_NOTE_USERQUOTA 129 
#define  ZFS_DELEG_NOTE_USERUSED 128 
 char* gettext (char*) ; 

__attribute__((used)) static inline const char *
deleg_perm_comment(zfs_deleg_note_t note)
{
	const char *str = "";

	/* subcommands */
	switch (note) {
		/* SUBCOMMANDS */
	case ZFS_DELEG_NOTE_ALLOW:
		str = gettext("Must also have the permission that is being"
		    "\n\t\t\t\tallowed");
		break;
	case ZFS_DELEG_NOTE_CLONE:
		str = gettext("Must also have the 'create' ability and 'mount'"
		    "\n\t\t\t\tability in the origin file system");
		break;
	case ZFS_DELEG_NOTE_CREATE:
		str = gettext("Must also have the 'mount' ability");
		break;
	case ZFS_DELEG_NOTE_DESTROY:
		str = gettext("Must also have the 'mount' ability");
		break;
	case ZFS_DELEG_NOTE_DIFF:
		str = gettext("Allows lookup of paths within a dataset;"
		    "\n\t\t\t\tgiven an object number. Ordinary users need this"
		    "\n\t\t\t\tin order to use zfs diff");
		break;
	case ZFS_DELEG_NOTE_HOLD:
		str = gettext("Allows adding a user hold to a snapshot");
		break;
	case ZFS_DELEG_NOTE_MOUNT:
		str = gettext("Allows mount/umount of ZFS datasets");
		break;
	case ZFS_DELEG_NOTE_PROMOTE:
		str = gettext("Must also have the 'mount'\n\t\t\t\tand"
		    " 'promote' ability in the origin file system");
		break;
	case ZFS_DELEG_NOTE_RECEIVE:
		str = gettext("Must also have the 'mount' and 'create'"
		    " ability");
		break;
	case ZFS_DELEG_NOTE_RELEASE:
		str = gettext("Allows releasing a user hold which\n\t\t\t\t"
		    "might destroy the snapshot");
		break;
	case ZFS_DELEG_NOTE_RENAME:
		str = gettext("Must also have the 'mount' and 'create'"
		    "\n\t\t\t\tability in the new parent");
		break;
	case ZFS_DELEG_NOTE_ROLLBACK:
		str = gettext("");
		break;
	case ZFS_DELEG_NOTE_SEND:
		str = gettext("");
		break;
	case ZFS_DELEG_NOTE_SHARE:
		str = gettext("Allows sharing file systems over NFS or SMB"
		    "\n\t\t\t\tprotocols");
		break;
	case ZFS_DELEG_NOTE_SNAPSHOT:
		str = gettext("");
		break;
	case ZFS_DELEG_NOTE_LOAD_KEY:
		str = gettext("Allows loading or unloading an encryption key");
		break;
	case ZFS_DELEG_NOTE_CHANGE_KEY:
		str = gettext("Allows changing or adding an encryption key");
		break;
/*
 *	case ZFS_DELEG_NOTE_VSCAN:
 *		str = gettext("");
 *		break;
 */
		/* OTHER */
	case ZFS_DELEG_NOTE_GROUPQUOTA:
		str = gettext("Allows accessing any groupquota@... property");
		break;
	case ZFS_DELEG_NOTE_GROUPUSED:
		str = gettext("Allows reading any groupused@... property");
		break;
	case ZFS_DELEG_NOTE_USERPROP:
		str = gettext("Allows changing any user property");
		break;
	case ZFS_DELEG_NOTE_USERQUOTA:
		str = gettext("Allows accessing any userquota@... property");
		break;
	case ZFS_DELEG_NOTE_USERUSED:
		str = gettext("Allows reading any userused@... property");
		break;
	case ZFS_DELEG_NOTE_USEROBJQUOTA:
		str = gettext("Allows accessing any userobjquota@... property");
		break;
	case ZFS_DELEG_NOTE_GROUPOBJQUOTA:
		str = gettext("Allows accessing any \n\t\t\t\t"
		    "groupobjquota@... property");
		break;
	case ZFS_DELEG_NOTE_GROUPOBJUSED:
		str = gettext("Allows reading any groupobjused@... property");
		break;
	case ZFS_DELEG_NOTE_USEROBJUSED:
		str = gettext("Allows reading any userobjused@... property");
		break;
	case ZFS_DELEG_NOTE_PROJECTQUOTA:
		str = gettext("Allows accessing any projectquota@... property");
		break;
	case ZFS_DELEG_NOTE_PROJECTOBJQUOTA:
		str = gettext("Allows accessing any \n\t\t\t\t"
		    "projectobjquota@... property");
		break;
	case ZFS_DELEG_NOTE_PROJECTUSED:
		str = gettext("Allows reading any projectused@... property");
		break;
	case ZFS_DELEG_NOTE_PROJECTOBJUSED:
		str = gettext("Allows accessing any \n\t\t\t\t"
		    "projectobjused@... property");
		break;
		/* other */
	default:
		str = "";
	}

	return (str);
}