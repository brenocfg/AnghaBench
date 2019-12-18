#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int z_dnodesize; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_mode; int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_24__ {int z_fuid_cnt; int /*<<< orphan*/  z_domain_cnt; void* z_fuid_group; void* z_fuid_owner; scalar_t__ z_domain_str_sz; } ;
typedef  TYPE_2__ zfs_fuid_info_t ;
struct TYPE_25__ {int /*<<< orphan*/  xva_mapsize; } ;
typedef  TYPE_3__ xvattr_t ;
struct TYPE_26__ {int vsa_aclflags; char* vsa_aclentp; int /*<<< orphan*/  vsa_aclcnt; } ;
typedef  TYPE_4__ vsecattr_t ;
struct TYPE_27__ {int va_mask; } ;
typedef  TYPE_5__ vattr_t ;
typedef  void* uint64_t ;
struct TYPE_28__ {scalar_t__ lr_rdev; scalar_t__* lr_crtime; scalar_t__ lr_gen; void* lr_gid; void* lr_uid; int /*<<< orphan*/  lr_mode; int /*<<< orphan*/  lr_foid; int /*<<< orphan*/  lr_doid; } ;
typedef  TYPE_6__ lr_create_t ;
typedef  int /*<<< orphan*/  lr_attr_t ;
struct TYPE_29__ {size_t lr_acl_bytes; int lr_fuidcnt; void* lr_acl_flags; int /*<<< orphan*/  lr_domcnt; int /*<<< orphan*/  lr_aclcnt; } ;
typedef  TYPE_7__ lr_acl_create_t ;
struct TYPE_30__ {int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_8__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  void* caddr_t ;

/* Variables and functions */
 int ATTR_XVATTR ; 
 int DNODE_SHIFT ; 
 int /*<<< orphan*/  IS_EPHEMERAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KGID_TO_SGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LR_FOID_SET_SLOTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SA_ZPL_CRTIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ZPL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ZPL_RDEV (int /*<<< orphan*/ ) ; 
 int TX_CREATE ; 
 int TX_CREATE_ATTR ; 
 int TX_MKDIR ; 
 int TX_MKDIR_ATTR ; 
 int TX_MKXATTR ; 
 int VSA_ACE_ACLFLAGS ; 
 int ZIL_ACE_LENGTH (size_t) ; 
 size_t ZIL_XVAT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZTOGID (TYPE_1__*) ; 
 int /*<<< orphan*/  ZTOUID (TYPE_1__*) ; 
 int /*<<< orphan*/  ZTOZSB (TYPE_1__*) ; 
 int /*<<< orphan*/  bcopy (char*,void*,size_t) ; 
 scalar_t__ sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int strlen (char*) ; 
 void* zfs_log_fuid_domains (TYPE_2__*,void*) ; 
 void* zfs_log_fuid_ids (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  zfs_log_xvattr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ zfs_xattr_owner_unlinked (TYPE_1__*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_8__* zil_itx_create (void*,size_t) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
zfs_log_create(zilog_t *zilog, dmu_tx_t *tx, uint64_t txtype,
    znode_t *dzp, znode_t *zp, char *name, vsecattr_t *vsecp,
    zfs_fuid_info_t *fuidp, vattr_t *vap)
{
	itx_t *itx;
	lr_create_t *lr;
	lr_acl_create_t *lracl;
	size_t aclsize = 0;
	size_t xvatsize = 0;
	size_t txsize;
	xvattr_t *xvap = (xvattr_t *)vap;
	void *end;
	size_t lrsize;
	size_t namesize = strlen(name) + 1;
	size_t fuidsz = 0;

	if (zil_replaying(zilog, tx) || zfs_xattr_owner_unlinked(dzp))
		return;

	/*
	 * If we have FUIDs present then add in space for
	 * domains and ACE fuid's if any.
	 */
	if (fuidp) {
		fuidsz += fuidp->z_domain_str_sz;
		fuidsz += fuidp->z_fuid_cnt * sizeof (uint64_t);
	}

	if (vap->va_mask & ATTR_XVATTR)
		xvatsize = ZIL_XVAT_SIZE(xvap->xva_mapsize);

	if ((int)txtype == TX_CREATE_ATTR || (int)txtype == TX_MKDIR_ATTR ||
	    (int)txtype == TX_CREATE || (int)txtype == TX_MKDIR ||
	    (int)txtype == TX_MKXATTR) {
		txsize = sizeof (*lr) + namesize + fuidsz + xvatsize;
		lrsize = sizeof (*lr);
	} else {
		txsize =
		    sizeof (lr_acl_create_t) + namesize + fuidsz +
		    ZIL_ACE_LENGTH(aclsize) + xvatsize;
		lrsize = sizeof (lr_acl_create_t);
	}

	itx = zil_itx_create(txtype, txsize);

	lr = (lr_create_t *)&itx->itx_lr;
	lr->lr_doid = dzp->z_id;
	lr->lr_foid = zp->z_id;
	/* Store dnode slot count in 8 bits above object id. */
	LR_FOID_SET_SLOTS(lr->lr_foid, zp->z_dnodesize >> DNODE_SHIFT);
	lr->lr_mode = zp->z_mode;
	if (!IS_EPHEMERAL(KUID_TO_SUID(ZTOUID(zp)))) {
		lr->lr_uid = (uint64_t)KUID_TO_SUID(ZTOUID(zp));
	} else {
		lr->lr_uid = fuidp->z_fuid_owner;
	}
	if (!IS_EPHEMERAL(KGID_TO_SGID(ZTOGID(zp)))) {
		lr->lr_gid = (uint64_t)KGID_TO_SGID(ZTOGID(zp));
	} else {
		lr->lr_gid = fuidp->z_fuid_group;
	}
	(void) sa_lookup(zp->z_sa_hdl, SA_ZPL_GEN(ZTOZSB(zp)), &lr->lr_gen,
	    sizeof (uint64_t));
	(void) sa_lookup(zp->z_sa_hdl, SA_ZPL_CRTIME(ZTOZSB(zp)),
	    lr->lr_crtime, sizeof (uint64_t) * 2);

	if (sa_lookup(zp->z_sa_hdl, SA_ZPL_RDEV(ZTOZSB(zp)), &lr->lr_rdev,
	    sizeof (lr->lr_rdev)) != 0)
		lr->lr_rdev = 0;

	/*
	 * Fill in xvattr info if any
	 */
	if (vap->va_mask & ATTR_XVATTR) {
		zfs_log_xvattr((lr_attr_t *)((caddr_t)lr + lrsize), xvap);
		end = (caddr_t)lr + lrsize + xvatsize;
	} else {
		end = (caddr_t)lr + lrsize;
	}

	/* Now fill in any ACL info */

	if (vsecp) {
		lracl = (lr_acl_create_t *)&itx->itx_lr;
		lracl->lr_aclcnt = vsecp->vsa_aclcnt;
		lracl->lr_acl_bytes = aclsize;
		lracl->lr_domcnt = fuidp ? fuidp->z_domain_cnt : 0;
		lracl->lr_fuidcnt  = fuidp ? fuidp->z_fuid_cnt : 0;
		if (vsecp->vsa_aclflags & VSA_ACE_ACLFLAGS)
			lracl->lr_acl_flags = (uint64_t)vsecp->vsa_aclflags;
		else
			lracl->lr_acl_flags = 0;

		bcopy(vsecp->vsa_aclentp, end, aclsize);
		end = (caddr_t)end + ZIL_ACE_LENGTH(aclsize);
	}

	/* drop in FUID info */
	if (fuidp) {
		end = zfs_log_fuid_ids(fuidp, end);
		end = zfs_log_fuid_domains(fuidp, end);
	}
	/*
	 * Now place file name in log record
	 */
	bcopy(name, end, namesize);

	zil_itx_assign(zilog, itx, tx);
}