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
typedef  int /*<<< orphan*/  znode_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_APPEND_DATA ; 
 scalar_t__ ACE_WRITE_DATA ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EACCES ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int zfs_zaccess_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_zaccess_append(znode_t *zp, uint32_t *working_mode, boolean_t *check_privs,
    cred_t *cr)
{
	if (*working_mode != ACE_WRITE_DATA)
		return (SET_ERROR(EACCES));

	return (zfs_zaccess_common(zp, ACE_APPEND_DATA, working_mode,
	    check_privs, B_FALSE, cr));
}