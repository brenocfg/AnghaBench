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
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_4__ {void* coerce_funcid; int /*<<< orphan*/ * tce; void* argtype; } ;
typedef  TYPE_1__ PartFuncCache ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 TYPE_1__* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PartFuncCache *
part_func_cache_create(Oid argtype, TypeCacheEntry *tce, Oid coerce_funcid, MemoryContext mcxt)
{
	PartFuncCache *pfc;

	pfc = MemoryContextAlloc(mcxt, sizeof(PartFuncCache));
	pfc->argtype = argtype;
	pfc->tce = tce;
	pfc->coerce_funcid = coerce_funcid;

	return pfc;
}