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
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ PROP_TYPE_STRING ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  strncpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_prop_default_numeric (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_default_string (scalar_t__) ; 
 scalar_t__ zfs_prop_get_type (scalar_t__) ; 
 scalar_t__ zfs_prop_readonly (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_setonce (scalar_t__) ; 

__attribute__((used)) static int
dodefault(zfs_prop_t prop, int intsz, int numints, void *buf)
{
	/*
	 * The setonce properties are read-only, BUT they still
	 * have a default value that can be used as the initial
	 * value.
	 */
	if (prop == ZPROP_INVAL ||
	    (zfs_prop_readonly(prop) && !zfs_prop_setonce(prop)))
		return (SET_ERROR(ENOENT));

	if (zfs_prop_get_type(prop) == PROP_TYPE_STRING) {
		if (intsz != 1)
			return (SET_ERROR(EOVERFLOW));
		(void) strncpy(buf, zfs_prop_default_string(prop),
		    numints);
	} else {
		if (intsz != 8 || numints < 1)
			return (SET_ERROR(EOVERFLOW));

		*(uint64_t *)buf = zfs_prop_default_numeric(prop);
	}

	return (0);
}