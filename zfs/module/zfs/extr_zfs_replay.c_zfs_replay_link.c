#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_4__ {int lrc_txtype; } ;
struct TYPE_5__ {TYPE_1__ lr_common; int /*<<< orphan*/  lr_link_obj; int /*<<< orphan*/  lr_doid; } ;
typedef  TYPE_2__ lr_link_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int FIGNORECASE ; 
 int TX_CI ; 
 int /*<<< orphan*/  ZTOI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_2__*,int) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcred ; 
 int zfs_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int zfs_zget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
zfs_replay_link(void *arg1, void *arg2, boolean_t byteswap)
{
	zfsvfs_t *zfsvfs = arg1;
	lr_link_t *lr = arg2;
	char *name = (char *)(lr + 1);	/* name follows lr_link_t */
	znode_t *dzp, *zp;
	int error;
	int vflg = 0;

	if (byteswap)
		byteswap_uint64_array(lr, sizeof (*lr));

	if ((error = zfs_zget(zfsvfs, lr->lr_doid, &dzp)) != 0)
		return (error);

	if ((error = zfs_zget(zfsvfs, lr->lr_link_obj, &zp)) != 0) {
		iput(ZTOI(dzp));
		return (error);
	}

	if (lr->lr_common.lrc_txtype & TX_CI)
		vflg |= FIGNORECASE;

	error = zfs_link(ZTOI(dzp), ZTOI(zp), name, kcred, vflg);

	iput(ZTOI(zp));
	iput(ZTOI(dzp));

	return (error);
}