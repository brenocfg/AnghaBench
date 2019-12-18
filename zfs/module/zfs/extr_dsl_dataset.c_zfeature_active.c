#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int fi_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  ZFEATURE_TYPE_BOOLEAN 129 
#define  ZFEATURE_TYPE_UINT64_ARRAY 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_1__* spa_feature_table ; 

__attribute__((used)) static boolean_t
zfeature_active(spa_feature_t f, void *arg)
{
	switch (spa_feature_table[f].fi_type) {
	case ZFEATURE_TYPE_BOOLEAN: {
		boolean_t val = (boolean_t)arg;
		ASSERT(val == B_FALSE || val == B_TRUE);
		return (val);
	}
	case ZFEATURE_TYPE_UINT64_ARRAY:
		/*
		 * In this case, arg is a uint64_t array.  The feature is active
		 * if the array is non-null.
		 */
		return (arg != NULL);
	default:
		panic("Invalid zfeature type %d", spa_feature_table[f].fi_type);
		return (B_FALSE);
	}
}