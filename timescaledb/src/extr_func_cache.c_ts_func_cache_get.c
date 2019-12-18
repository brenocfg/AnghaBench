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
struct TYPE_3__ {int /*<<< orphan*/ * funcinfo; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FuncInfo ;
typedef  TYPE_1__ FuncEntry ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/ * func_hash ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_func_info () ; 

FuncInfo *
ts_func_cache_get(Oid funcid)
{
	FuncEntry *entry;

	if (NULL == func_hash)
		initialize_func_info();

	entry = hash_search(func_hash, &funcid, HASH_FIND, NULL);

	return (NULL == entry) ? NULL : entry->funcinfo;
}