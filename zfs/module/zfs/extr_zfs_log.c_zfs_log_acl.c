#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ z_sync_cnt; int /*<<< orphan*/  z_id; scalar_t__ z_unlinked; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_17__ {int z_domain_str_sz; int z_fuid_cnt; int /*<<< orphan*/  z_domain_cnt; } ;
typedef  TYPE_2__ zfs_fuid_info_t ;
struct TYPE_18__ {size_t vsa_aclentsz; int vsa_mask; int /*<<< orphan*/  vsa_aclentp; int /*<<< orphan*/  vsa_aclcnt; int /*<<< orphan*/  vsa_aclflags; } ;
typedef  TYPE_3__ vsecattr_t ;
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  lr_acl_v0_t ;
struct TYPE_19__ {size_t lr_acl_bytes; int lr_fuidcnt; void* lr_aclcnt; void* lr_acl_flags; int /*<<< orphan*/  lr_domcnt; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_4__ lr_acl_t ;
struct TYPE_20__ {int itx_sync; int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_5__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int caddr_t ;
typedef  void ace_t ;
struct TYPE_15__ {scalar_t__ z_version; } ;

/* Variables and functions */
 int TX_ACL ; 
 int TX_ACL_V0 ; 
 int VSA_ACE_ACLFLAGS ; 
 size_t ZIL_ACE_LENGTH (size_t) ; 
 scalar_t__ ZPL_VERSION_FUID ; 
 TYPE_13__* ZTOZSB (TYPE_1__*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  zfs_log_fuid_domains (TYPE_2__*,void*) ; 
 void* zfs_log_fuid_ids (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* zil_itx_create (int,size_t) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
zfs_log_acl(zilog_t *zilog, dmu_tx_t *tx, znode_t *zp,
    vsecattr_t *vsecp, zfs_fuid_info_t *fuidp)
{
	itx_t *itx;
	lr_acl_v0_t *lrv0;
	lr_acl_t *lr;
	int txtype;
	int lrsize;
	size_t txsize;
	size_t aclbytes = vsecp->vsa_aclentsz;

	if (zil_replaying(zilog, tx) || zp->z_unlinked)
		return;

	txtype = (ZTOZSB(zp)->z_version < ZPL_VERSION_FUID) ?
	    TX_ACL_V0 : TX_ACL;

	if (txtype == TX_ACL)
		lrsize = sizeof (*lr);
	else
		lrsize = sizeof (*lrv0);

	txsize = lrsize +
	    ((txtype == TX_ACL) ? ZIL_ACE_LENGTH(aclbytes) : aclbytes) +
	    (fuidp ? fuidp->z_domain_str_sz : 0) +
	    sizeof (uint64_t) * (fuidp ? fuidp->z_fuid_cnt : 0);

	itx = zil_itx_create(txtype, txsize);

	lr = (lr_acl_t *)&itx->itx_lr;
	lr->lr_foid = zp->z_id;
	if (txtype == TX_ACL) {
		lr->lr_acl_bytes = aclbytes;
		lr->lr_domcnt = fuidp ? fuidp->z_domain_cnt : 0;
		lr->lr_fuidcnt = fuidp ? fuidp->z_fuid_cnt : 0;
		if (vsecp->vsa_mask & VSA_ACE_ACLFLAGS)
			lr->lr_acl_flags = (uint64_t)vsecp->vsa_aclflags;
		else
			lr->lr_acl_flags = 0;
	}
	lr->lr_aclcnt = (uint64_t)vsecp->vsa_aclcnt;

	if (txtype == TX_ACL_V0) {
		lrv0 = (lr_acl_v0_t *)lr;
		bcopy(vsecp->vsa_aclentp, (ace_t *)(lrv0 + 1), aclbytes);
	} else {
		void *start = (ace_t *)(lr + 1);

		bcopy(vsecp->vsa_aclentp, start, aclbytes);

		start = (caddr_t)start + ZIL_ACE_LENGTH(aclbytes);

		if (fuidp) {
			start = zfs_log_fuid_ids(fuidp, start);
			(void) zfs_log_fuid_domains(fuidp, start);
		}
	}

	itx->itx_sync = (zp->z_sync_cnt != 0);
	zil_itx_assign(zilog, itx, tx);
}