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
struct TYPE_13__ {int /*<<< orphan*/  cmp; int /*<<< orphan*/  value; } ;
struct TYPE_12__ {int /*<<< orphan*/  is_null; } ;
typedef  TYPE_2__ PolyDatum ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ InternalCmpAggStore ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (TYPE_3__*) ; 
 scalar_t__ cmpfunccache_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__,int /*<<< orphan*/ ) ; 
 TYPE_1__* transcache_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeinfocache_polydatumcopy (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline Datum
bookend_sfunc(MemoryContext aggcontext, InternalCmpAggStore *state, PolyDatum value, PolyDatum cmp,
			  char *opname, FunctionCallInfo fcinfo)
{
	MemoryContext old_context;
	TransCache *cache = transcache_get(fcinfo);

	old_context = MemoryContextSwitchTo(aggcontext);

	if (state == NULL)
	{
		state = (InternalCmpAggStore *) MemoryContextAlloc(aggcontext, sizeof(InternalCmpAggStore));
		typeinfocache_polydatumcopy(&cache->value_type_cache, value, &state->value);
		typeinfocache_polydatumcopy(&cache->cmp_type_cache, cmp, &state->cmp);
	}
	else
	{
		/* only do comparison if cmp is not NULL */
		if (!cmp.is_null &&
			cmpfunccache_cmp(&cache->cmp_func_cache, fcinfo, opname, cmp, state->cmp))
		{
			typeinfocache_polydatumcopy(&cache->value_type_cache, value, &state->value);
			typeinfocache_polydatumcopy(&cache->cmp_type_cache, cmp, &state->cmp);
		}
	}
	MemoryContextSwitchTo(old_context);

	PG_RETURN_POINTER(state);
}