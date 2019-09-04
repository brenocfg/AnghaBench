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
struct TYPE_3__ {int /*<<< orphan*/ * entry; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ CustomEstimateForFunctionInfoHashEntry ;
typedef  int /*<<< orphan*/  CustomEstimateForFunctionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/ * custom_estimate_func_hash ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_custom_estimate_func_info () ; 

__attribute__((used)) static CustomEstimateForFunctionInfo *
get_custom_estimate_func_info(Oid function_oid)
{
	CustomEstimateForFunctionInfoHashEntry *hash_entry;

	if (NULL == custom_estimate_func_hash)
		initialize_custom_estimate_func_info();

	hash_entry = hash_search(custom_estimate_func_hash, &function_oid, HASH_FIND, NULL);
	return (hash_entry != NULL ? hash_entry->entry : NULL);
}