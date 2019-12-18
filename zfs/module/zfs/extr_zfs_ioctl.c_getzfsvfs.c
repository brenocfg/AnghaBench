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
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int getzfsvfs_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
getzfsvfs(const char *dsname, zfsvfs_t **zfvp)
{
	objset_t *os;
	int error;

	error = dmu_objset_hold(dsname, FTAG, &os);
	if (error != 0)
		return (error);

	error = getzfsvfs_impl(os, zfvp);
	dmu_objset_rele(os, FTAG);
	return (error);
}