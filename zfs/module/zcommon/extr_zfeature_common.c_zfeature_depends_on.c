#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* fi_depends; } ;
typedef  TYPE_1__ zfeature_info_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ SPA_FEATURE_NONE ; 
 TYPE_1__* spa_feature_table ; 

boolean_t
zfeature_depends_on(spa_feature_t fid, spa_feature_t check)
{
	zfeature_info_t *feature = &spa_feature_table[fid];

	for (int i = 0; feature->fi_depends[i] != SPA_FEATURE_NONE; i++) {
		if (feature->fi_depends[i] == check)
			return (B_TRUE);
	}
	return (B_FALSE);
}