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
struct TYPE_4__ {int /*<<< orphan*/ * z_xattr_cached; int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_xattr_lock; } ;
typedef  TYPE_1__ znode_t ;
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ *) ; 
 int ERANGE ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 int /*<<< orphan*/ * RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int nvlist_lookup_byte_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int*) ; 
 int zfs_sa_get_xattr (TYPE_1__*) ; 

__attribute__((used)) static int
zpl_xattr_get_sa(struct inode *ip, const char *name, void *value, size_t size)
{
	znode_t *zp = ITOZ(ip);
	uchar_t *nv_value;
	uint_t nv_size;
	int error = 0;

	ASSERT(RW_LOCK_HELD(&zp->z_xattr_lock));

	mutex_enter(&zp->z_lock);
	if (zp->z_xattr_cached == NULL)
		error = -zfs_sa_get_xattr(zp);
	mutex_exit(&zp->z_lock);

	if (error)
		return (error);

	ASSERT(zp->z_xattr_cached);
	error = -nvlist_lookup_byte_array(zp->z_xattr_cached, name,
	    &nv_value, &nv_size);
	if (error)
		return (error);

	if (size == 0 || value == NULL)
		return (nv_size);

	if (size < nv_size)
		return (-ERANGE);

	memcpy(value, nv_value, nv_size);

	return (nv_size);
}