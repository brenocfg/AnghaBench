#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ is_bucketing_func; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ FuncInfo ;

/* Variables and functions */
 TYPE_1__* ts_func_cache_get (int /*<<< orphan*/ ) ; 

FuncInfo *
ts_func_cache_get_bucketing_func(Oid funcid)
{
	FuncInfo *finfo = ts_func_cache_get(funcid);

	if (NULL == finfo)
		return NULL;

	return finfo->is_bucketing_func ? finfo : NULL;
}