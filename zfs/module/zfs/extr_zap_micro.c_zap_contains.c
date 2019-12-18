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
 int EINVAL ; 
 int EOVERFLOW ; 
 int zap_lookup_norm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zap_contains(objset_t *os, uint64_t zapobj, const char *name)
{
	int err = zap_lookup_norm(os, zapobj, name, 0,
	    0, NULL, 0, NULL, 0, NULL);
	if (err == EOVERFLOW || err == EINVAL)
		err = 0; /* found, but skipped reading the value */
	return (err);
}