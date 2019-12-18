#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_4__ {int /*<<< orphan*/  z_inherit_type; int /*<<< orphan*/  z_object_type; } ;
typedef  TYPE_1__ zfs_object_ace_t ;
typedef  int /*<<< orphan*/  zfs_acl_t ;
typedef  int /*<<< orphan*/  zfs_ace_hdr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {int a_flags; int a_type; int /*<<< orphan*/  a_access_mask; scalar_t__ a_who; } ;
typedef  TYPE_2__ ace_t ;
struct TYPE_6__ {int /*<<< orphan*/  a_inherit_obj_type; int /*<<< orphan*/  a_obj_type; } ;
typedef  TYPE_3__ ace_object_t ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE 131 
#define  ACE_ACCESS_DENIED_OBJECT_ACE_TYPE 130 
 int ACE_EVERYONE ; 
 int ACE_IDENTIFIER_GROUP ; 
 int ACE_OWNER ; 
#define  ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE 129 
#define  ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE 128 
 int ACE_TYPE_FLAGS ; 
 int OWNING_GROUP ; 
 int /*<<< orphan*/  ZFS_ACE_GROUP ; 
 int /*<<< orphan*/  ZFS_ACE_USER ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zfs_acl_next_ace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ zfs_fuid_map_id (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zfs_copy_fuid_2_ace(zfsvfs_t *zfsvfs, zfs_acl_t *aclp, cred_t *cr,
    void *datap, int filter)
{
	uint64_t who;
	uint32_t access_mask;
	uint16_t iflags, type;
	zfs_ace_hdr_t *zacep = NULL;
	ace_t *acep = datap;
	ace_object_t *objacep;
	zfs_object_ace_t *zobjacep;
	size_t ace_size;
	uint16_t entry_type;

	while ((zacep = zfs_acl_next_ace(aclp, zacep,
	    &who, &access_mask, &iflags, &type))) {

		switch (type) {
		case ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE:
		case ACE_ACCESS_DENIED_OBJECT_ACE_TYPE:
		case ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE:
		case ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE:
			if (filter) {
				continue;
			}
			zobjacep = (zfs_object_ace_t *)zacep;
			objacep = (ace_object_t *)acep;
			bcopy(zobjacep->z_object_type,
			    objacep->a_obj_type,
			    sizeof (zobjacep->z_object_type));
			bcopy(zobjacep->z_inherit_type,
			    objacep->a_inherit_obj_type,
			    sizeof (zobjacep->z_inherit_type));
			ace_size = sizeof (ace_object_t);
			break;
		default:
			ace_size = sizeof (ace_t);
			break;
		}

		entry_type = (iflags & ACE_TYPE_FLAGS);
		if ((entry_type != ACE_OWNER &&
		    entry_type != OWNING_GROUP &&
		    entry_type != ACE_EVERYONE)) {
			acep->a_who = zfs_fuid_map_id(zfsvfs, who,
			    cr, (entry_type & ACE_IDENTIFIER_GROUP) ?
			    ZFS_ACE_GROUP : ZFS_ACE_USER);
		} else {
			acep->a_who = (uid_t)(int64_t)who;
		}
		acep->a_access_mask = access_mask;
		acep->a_flags = iflags;
		acep->a_type = type;
		acep = (ace_t *)((caddr_t)acep + ace_size);
	}
}