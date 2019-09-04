#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  cmp_type_cache; int /*<<< orphan*/  value_type_cache; int /*<<< orphan*/  cmp_func_cache; } ;
typedef  TYPE_1__ TransCache ;
struct TYPE_13__ {scalar_t__ is_null; } ;
struct TYPE_12__ {TYPE_3__ cmp; TYPE_3__ value; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ InternalCmpAggStore ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (TYPE_2__*) ; 
 scalar_t__ cmpfunccache_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__,TYPE_3__) ; 
 TYPE_1__* transcache_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeinfocache_polydatumcopy (int /*<<< orphan*/ *,TYPE_3__,TYPE_3__*) ; 

__attribute__((used)) static inline Datum
bookend_combinefunc(MemoryContext aggcontext, InternalCmpAggStore *state1,
					InternalCmpAggStore *state2, char *opname, FunctionCallInfo fcinfo)
{
	MemoryContext old_context;
	TransCache *cache;

	if (state2 == NULL)
		PG_RETURN_POINTER(state1);

	cache = transcache_get(fcinfo);

	/*
	 * manually copy all fields from state2 to state1, as per other combine
	 * func like int8_avg_combine
	 */
	if (state1 == NULL)
	{
		old_context = MemoryContextSwitchTo(aggcontext);

		state1 =
			(InternalCmpAggStore *) MemoryContextAlloc(aggcontext, sizeof(InternalCmpAggStore));
		typeinfocache_polydatumcopy(&cache->value_type_cache, state2->value, &state1->value);
		typeinfocache_polydatumcopy(&cache->cmp_type_cache, state2->cmp, &state1->cmp);

		MemoryContextSwitchTo(old_context);
		PG_RETURN_POINTER(state1);
	}

	if (state1->cmp.is_null && state2->cmp.is_null)
	{
		PG_RETURN_POINTER(state1);
	}
	else if (state1->cmp.is_null != state2->cmp.is_null)
	{
		if (state1->cmp.is_null)
			PG_RETURN_POINTER(state2);
		else
			PG_RETURN_POINTER(state1);
	}
	else if (cmpfunccache_cmp(&cache->cmp_func_cache, fcinfo, opname, state2->cmp, state1->cmp))
	{
		old_context = MemoryContextSwitchTo(aggcontext);
		typeinfocache_polydatumcopy(&cache->value_type_cache, state2->value, &state1->value);
		typeinfocache_polydatumcopy(&cache->cmp_type_cache, state2->cmp, &state1->cmp);
		MemoryContextSwitchTo(old_context);
	}

	PG_RETURN_POINTER(state1);
}