#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_8__ {scalar_t__ z_norm; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {char* pn_buf; size_t pn_bufsize; } ;
typedef  TYPE_3__ pathname_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int ED_CASE_CONFLICT ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  ZFS_DIRENT_OBJ (int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *) ; 
 int zap_lookup_norm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,scalar_t__*) ; 

__attribute__((used)) static int
zfs_match_find(zfsvfs_t *zfsvfs, znode_t *dzp, char *name, matchtype_t mt,
    boolean_t update, int *deflags, pathname_t *rpnp, uint64_t *zoid)
{
	boolean_t conflict = B_FALSE;
	int error;

	if (zfsvfs->z_norm) {
		size_t bufsz = 0;
		char *buf = NULL;

		if (rpnp) {
			buf = rpnp->pn_buf;
			bufsz = rpnp->pn_bufsize;
		}

		/*
		 * In the non-mixed case we only expect there would ever
		 * be one match, but we need to use the normalizing lookup.
		 */
		error = zap_lookup_norm(zfsvfs->z_os, dzp->z_id, name, 8, 1,
		    zoid, mt, buf, bufsz, &conflict);
	} else {
		error = zap_lookup(zfsvfs->z_os, dzp->z_id, name, 8, 1, zoid);
	}

	/*
	 * Allow multiple entries provided the first entry is
	 * the object id.  Non-zpl consumers may safely make
	 * use of the additional space.
	 *
	 * XXX: This should be a feature flag for compatibility
	 */
	if (error == EOVERFLOW)
		error = 0;

	if (zfsvfs->z_norm && !error && deflags)
		*deflags = conflict ? ED_CASE_CONFLICT : 0;

	*zoid = ZFS_DIRENT_OBJ(*zoid);

	return (error);
}