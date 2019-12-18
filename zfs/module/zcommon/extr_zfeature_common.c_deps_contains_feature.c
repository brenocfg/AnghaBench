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
typedef  scalar_t__ spa_feature_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ const SPA_FEATURE_NONE ; 

__attribute__((used)) static boolean_t
deps_contains_feature(const spa_feature_t *deps, const spa_feature_t feature)
{
	for (int i = 0; deps[i] != SPA_FEATURE_NONE; i++)
		if (deps[i] == feature)
			return (B_TRUE);

	return (B_FALSE);
}