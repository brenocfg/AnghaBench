#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int zil_create_t ;
typedef  int /*<<< orphan*/  vsecattr_t ;
struct TYPE_3__ {int va_mask; } ;
typedef  TYPE_1__ vattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ATTR_XVATTR ; 
 int TX_CREATE ; 
 int TX_CREATE_ACL ; 
 int TX_CREATE_ACL_ATTR ; 
 int TX_CREATE_ATTR ; 
 int TX_MAX_TYPE ; 
 int TX_MKDIR ; 
 int TX_MKDIR_ACL ; 
 int TX_MKDIR_ACL_ATTR ; 
 int TX_MKDIR_ATTR ; 
 int TX_MKXATTR ; 
#define  Z_DIR 130 
#define  Z_FILE 129 
#define  Z_XATTRDIR 128 

int
zfs_log_create_txtype(zil_create_t type, vsecattr_t *vsecp, vattr_t *vap)
{
	int isxvattr = (vap->va_mask & ATTR_XVATTR);
	switch (type) {
	case Z_FILE:
		if (vsecp == NULL && !isxvattr)
			return (TX_CREATE);
		if (vsecp && isxvattr)
			return (TX_CREATE_ACL_ATTR);
		if (vsecp)
			return (TX_CREATE_ACL);
		else
			return (TX_CREATE_ATTR);
		/*NOTREACHED*/
	case Z_DIR:
		if (vsecp == NULL && !isxvattr)
			return (TX_MKDIR);
		if (vsecp && isxvattr)
			return (TX_MKDIR_ACL_ATTR);
		if (vsecp)
			return (TX_MKDIR_ACL);
		else
			return (TX_MKDIR_ATTR);
	case Z_XATTRDIR:
		return (TX_MKXATTR);
	}
	ASSERT(0);
	return (TX_MAX_TYPE);
}