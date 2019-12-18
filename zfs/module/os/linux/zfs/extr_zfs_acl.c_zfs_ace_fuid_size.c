#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_object_ace_t ;
typedef  int /*<<< orphan*/  zfs_ace_t ;
struct TYPE_2__ {int z_type; int z_flags; } ;
typedef  TYPE_1__ zfs_ace_hdr_t ;
typedef  int uint16_t ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE 133 
#define  ACE_ACCESS_DENIED_OBJECT_ACE_TYPE 132 
 int ACE_EVERYONE ; 
 int ACE_OWNER ; 
#define  ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE 131 
#define  ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE 130 
 int ACE_TYPE_FLAGS ; 
#define  ALLOW 129 
#define  DENY 128 
 int OWNING_GROUP ; 

__attribute__((used)) static size_t
zfs_ace_fuid_size(void *acep)
{
	zfs_ace_hdr_t *zacep = acep;
	uint16_t entry_type;

	switch (zacep->z_type) {
	case ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE:
	case ACE_ACCESS_DENIED_OBJECT_ACE_TYPE:
	case ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE:
	case ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE:
		return (sizeof (zfs_object_ace_t));
	case ALLOW:
	case DENY:
		entry_type =
		    (((zfs_ace_hdr_t *)acep)->z_flags & ACE_TYPE_FLAGS);
		if (entry_type == ACE_OWNER ||
		    entry_type == OWNING_GROUP ||
		    entry_type == ACE_EVERYONE)
			return (sizeof (zfs_ace_hdr_t));
		/*FALLTHROUGH*/
	default:
		return (sizeof (zfs_ace_t));
	}
}