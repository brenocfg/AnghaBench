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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  VDEV_TYPE_MIRROR ; 
 int /*<<< orphan*/  VDEV_TYPE_RAIDZ ; 
 int /*<<< orphan*/  VDEV_TYPE_REPLACING ; 
 int /*<<< orphan*/  VDEV_TYPE_SPARE ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
zpool_vdev_is_interior(const char *name)
{
	if (strncmp(name, VDEV_TYPE_RAIDZ, strlen(VDEV_TYPE_RAIDZ)) == 0 ||
	    strncmp(name, VDEV_TYPE_SPARE, strlen(VDEV_TYPE_SPARE)) == 0 ||
	    strncmp(name,
	    VDEV_TYPE_REPLACING, strlen(VDEV_TYPE_REPLACING)) == 0 ||
	    strncmp(name, VDEV_TYPE_MIRROR, strlen(VDEV_TYPE_MIRROR)) == 0)
		return (B_TRUE);
	return (B_FALSE);
}