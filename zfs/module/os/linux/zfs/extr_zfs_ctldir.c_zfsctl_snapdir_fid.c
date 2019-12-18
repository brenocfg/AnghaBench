#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** zf_gen; void** zf_object; scalar_t__ zf_len; } ;
typedef  TYPE_1__ zfid_short_t ;
struct TYPE_6__ {scalar_t__* zf_setgen; void** zf_setid; } ;
typedef  TYPE_2__ zfid_long_t ;
typedef  void* uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct inode {int i_ino; } ;
struct dentry {int dummy; } ;
struct TYPE_7__ {scalar_t__ fid_len; } ;
typedef  TYPE_3__ fid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 scalar_t__ LONG_FID_LEN ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFSCTL_INO_SNAPDIRS ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 

__attribute__((used)) static int
zfsctl_snapdir_fid(struct inode *ip, fid_t *fidp)
{
	zfid_short_t *zfid = (zfid_short_t *)fidp;
	zfid_long_t *zlfid = (zfid_long_t *)fidp;
	uint32_t gen = 0;
	uint64_t object;
	uint64_t objsetid;
	int i;
	struct dentry *dentry;

	if (fidp->fid_len < LONG_FID_LEN) {
		fidp->fid_len = LONG_FID_LEN;
		return (SET_ERROR(ENOSPC));
	}

	object = ip->i_ino;
	objsetid = ZFSCTL_INO_SNAPDIRS - ip->i_ino;
	zfid->zf_len = LONG_FID_LEN;

	dentry = d_obtain_alias(igrab(ip));
	if (!IS_ERR(dentry)) {
		gen = !!d_mountpoint(dentry);
		dput(dentry);
	}

	for (i = 0; i < sizeof (zfid->zf_object); i++)
		zfid->zf_object[i] = (uint8_t)(object >> (8 * i));

	for (i = 0; i < sizeof (zfid->zf_gen); i++)
		zfid->zf_gen[i] = (uint8_t)(gen >> (8 * i));

	for (i = 0; i < sizeof (zlfid->zf_setid); i++)
		zlfid->zf_setid[i] = (uint8_t)(objsetid >> (8 * i));

	for (i = 0; i < sizeof (zlfid->zf_setgen); i++)
		zlfid->zf_setgen[i] = 0;

	return (0);
}