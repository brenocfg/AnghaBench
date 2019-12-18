#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ z_acl_inherit; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_14__ {size_t z_acl_bytes; int z_acl_count; int /*<<< orphan*/  z_acl; TYPE_1__* z_ops; int /*<<< orphan*/  z_hints; } ;
typedef  TYPE_3__ zfs_acl_t ;
struct TYPE_15__ {int z_ace_count; int z_size; void* z_acldata; } ;
typedef  TYPE_4__ zfs_acl_node_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_12__ {size_t (* ace_abstract_size ) () ;int (* ace_size ) (void*) ;} ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE 131 
#define  ACE_ACCESS_DENIED_OBJECT_ACE_TYPE 130 
 int ACE_APPEND_DATA ; 
 int ACE_EVERYONE ; 
 int ACE_EXECUTE ; 
 int ACE_INHERIT_ONLY_ACE ; 
 int ACE_OWNER ; 
 int ACE_READ_DATA ; 
#define  ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE 129 
#define  ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE 128 
 int ACE_TYPE_FLAGS ; 
 int ACE_WRITE_ACL ; 
 int ACE_WRITE_ATTRIBUTES ; 
 int ACE_WRITE_DATA ; 
 int ACE_WRITE_NAMED_ATTRS ; 
 int ACE_WRITE_OWNER ; 
 int ALLOW ; 
 int ALL_INHERIT ; 
 int DENY ; 
 int OWNING_GROUP ; 
 int S_IRGRP ; 
 int S_IWGRP ; 
 int S_IXGRP ; 
 int /*<<< orphan*/  ZFS_ACL_OBJ_ACE ; 
 scalar_t__ ZFS_ACL_RESTRICTED ; 
 int /*<<< orphan*/  ZFS_INHERIT_ACE ; 
 int /*<<< orphan*/  acl_trivial_access_masks (int /*<<< orphan*/ ,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_4__*) ; 
 size_t stub1 () ; 
 int stub2 (void*) ; 
 void* zfs_acl_next_ace (TYPE_3__*,void*,int*,int*,int*,int*) ; 
 TYPE_4__* zfs_acl_node_alloc (size_t) ; 
 int /*<<< orphan*/  zfs_acl_release_nodes (TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_set_ace (TYPE_3__*,void*,int,int,int,int) ; 

__attribute__((used)) static void
zfs_acl_chmod(zfsvfs_t *zfsvfs, uint64_t mode, zfs_acl_t *aclp)
{
	void		*acep = NULL;
	uint64_t	who;
	int		new_count, new_bytes;
	int		ace_size;
	int		entry_type;
	uint16_t	iflags, type;
	uint32_t	access_mask;
	zfs_acl_node_t	*newnode;
	size_t		abstract_size = aclp->z_ops->ace_abstract_size();
	void		*zacep;
	uint32_t	owner, group, everyone;
	uint32_t	deny1, deny2, allow0;

	new_count = new_bytes = 0;

	acl_trivial_access_masks((mode_t)mode, &allow0, &deny1, &deny2,
	    &owner, &group, &everyone);

	newnode = zfs_acl_node_alloc((abstract_size * 6) + aclp->z_acl_bytes);

	zacep = newnode->z_acldata;
	if (allow0) {
		zfs_set_ace(aclp, zacep, allow0, ALLOW, -1, ACE_OWNER);
		zacep = (void *)((uintptr_t)zacep + abstract_size);
		new_count++;
		new_bytes += abstract_size;
	}
	if (deny1) {
		zfs_set_ace(aclp, zacep, deny1, DENY, -1, ACE_OWNER);
		zacep = (void *)((uintptr_t)zacep + abstract_size);
		new_count++;
		new_bytes += abstract_size;
	}
	if (deny2) {
		zfs_set_ace(aclp, zacep, deny2, DENY, -1, OWNING_GROUP);
		zacep = (void *)((uintptr_t)zacep + abstract_size);
		new_count++;
		new_bytes += abstract_size;
	}

	while ((acep = zfs_acl_next_ace(aclp, acep, &who, &access_mask,
	    &iflags, &type))) {
		uint16_t inherit_flags;

		entry_type = (iflags & ACE_TYPE_FLAGS);
		inherit_flags = (iflags & ALL_INHERIT);

		if ((entry_type == ACE_OWNER || entry_type == ACE_EVERYONE ||
		    (entry_type == OWNING_GROUP)) &&
		    ((inherit_flags & ACE_INHERIT_ONLY_ACE) == 0)) {
			continue;
		}

		if ((type != ALLOW && type != DENY) ||
		    (inherit_flags & ACE_INHERIT_ONLY_ACE)) {
			if (inherit_flags)
				aclp->z_hints |= ZFS_INHERIT_ACE;
			switch (type) {
			case ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE:
			case ACE_ACCESS_DENIED_OBJECT_ACE_TYPE:
			case ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE:
			case ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE:
				aclp->z_hints |= ZFS_ACL_OBJ_ACE;
				break;
			}
		} else {

			/*
			 * Limit permissions to be no greater than
			 * group permissions
			 */
			if (zfsvfs->z_acl_inherit == ZFS_ACL_RESTRICTED) {
				if (!(mode & S_IRGRP))
					access_mask &= ~ACE_READ_DATA;
				if (!(mode & S_IWGRP))
					access_mask &=
					    ~(ACE_WRITE_DATA|ACE_APPEND_DATA);
				if (!(mode & S_IXGRP))
					access_mask &= ~ACE_EXECUTE;
				access_mask &=
				    ~(ACE_WRITE_OWNER|ACE_WRITE_ACL|
				    ACE_WRITE_ATTRIBUTES|ACE_WRITE_NAMED_ATTRS);
			}
		}
		zfs_set_ace(aclp, zacep, access_mask, type, who, iflags);
		ace_size = aclp->z_ops->ace_size(acep);
		zacep = (void *)((uintptr_t)zacep + ace_size);
		new_count++;
		new_bytes += ace_size;
	}
	zfs_set_ace(aclp, zacep, owner, 0, -1, ACE_OWNER);
	zacep = (void *)((uintptr_t)zacep + abstract_size);
	zfs_set_ace(aclp, zacep, group, 0, -1, OWNING_GROUP);
	zacep = (void *)((uintptr_t)zacep + abstract_size);
	zfs_set_ace(aclp, zacep, everyone, 0, -1, ACE_EVERYONE);

	new_count += 3;
	new_bytes += abstract_size * 3;
	zfs_acl_release_nodes(aclp);
	aclp->z_acl_count = new_count;
	aclp->z_acl_bytes = new_bytes;
	newnode->z_ace_count = new_count;
	newnode->z_size = new_bytes;
	list_insert_tail(&aclp->z_acl, newnode);
}