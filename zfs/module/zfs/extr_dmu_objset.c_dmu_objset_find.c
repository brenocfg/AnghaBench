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
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int dmu_objset_find_impl (int /*<<< orphan*/ *,char const*,int (*) (char const*,void*),void*,int) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int
dmu_objset_find(const char *name, int func(const char *, void *), void *arg,
    int flags)
{
	spa_t *spa;
	int error;

	error = spa_open(name, &spa, FTAG);
	if (error != 0)
		return (error);
	error = dmu_objset_find_impl(spa, name, func, arg, flags);
	spa_close(spa, FTAG);
	return (error);
}