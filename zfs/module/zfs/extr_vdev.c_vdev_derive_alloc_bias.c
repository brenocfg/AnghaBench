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
typedef  int /*<<< orphan*/  vdev_alloc_bias_t ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_ALLOC_BIAS_DEDUP ; 
 int /*<<< orphan*/  VDEV_ALLOC_BIAS_LOG ; 
 int /*<<< orphan*/  VDEV_ALLOC_BIAS_SPECIAL ; 
 int /*<<< orphan*/  VDEV_BIAS_DEDUP ; 
 int /*<<< orphan*/  VDEV_BIAS_LOG ; 
 int /*<<< orphan*/  VDEV_BIAS_NONE ; 
 int /*<<< orphan*/  VDEV_BIAS_SPECIAL ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vdev_alloc_bias_t
vdev_derive_alloc_bias(const char *bias)
{
	vdev_alloc_bias_t alloc_bias = VDEV_BIAS_NONE;

	if (strcmp(bias, VDEV_ALLOC_BIAS_LOG) == 0)
		alloc_bias = VDEV_BIAS_LOG;
	else if (strcmp(bias, VDEV_ALLOC_BIAS_SPECIAL) == 0)
		alloc_bias = VDEV_BIAS_SPECIAL;
	else if (strcmp(bias, VDEV_ALLOC_BIAS_DEDUP) == 0)
		alloc_bias = VDEV_BIAS_DEDUP;

	return (alloc_bias);
}