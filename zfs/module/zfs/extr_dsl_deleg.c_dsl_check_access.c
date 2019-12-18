#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EPERM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DELEG_NAME ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_deleg_whokey (char*,char,char,void*) ; 

__attribute__((used)) static int
dsl_check_access(objset_t *mos, uint64_t zapobj,
    char type, char checkflag, void *valp, const char *perm)
{
	int error;
	uint64_t jumpobj, zero;
	char whokey[ZFS_MAX_DELEG_NAME];

	zfs_deleg_whokey(whokey, type, checkflag, valp);
	error = zap_lookup(mos, zapobj, whokey, 8, 1, &jumpobj);
	if (error == 0) {
		error = zap_lookup(mos, jumpobj, perm, 8, 1, &zero);
		if (error == ENOENT)
			error = SET_ERROR(EPERM);
	}
	return (error);
}