#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  table_id; } ;
struct TYPE_6__ {size_t call_cntr; size_t max_calls; scalar_t__ user_fctx; } ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_1__ FuncCallContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SRF_IS_FIRSTCALL () ; 
 TYPE_1__* SRF_PERCALL_SETUP () ; 
 int /*<<< orphan*/  SRF_RETURN_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  SRF_RETURN_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPEFUNC_SCALAR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Datum
chunks_return_srf(FunctionCallInfo fcinfo)
{
	FuncCallContext *funcctx;
	uint64 call_cntr;
	TupleDesc tupdesc;
	Chunk **result_set;

	/* stuff done only on the first call of the function */
	if (SRF_IS_FIRSTCALL())
	{
		/* Build a tuple descriptor for our result type */
		/* not quite necessary */
		if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_SCALAR)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("function returning record called in context "
							"that cannot accept type record")));
	}

	/* stuff done on every call of the function */
	funcctx = SRF_PERCALL_SETUP();

	call_cntr = funcctx->call_cntr;
	result_set = (Chunk **) funcctx->user_fctx;

	/* do when there is more left to send */
	if (call_cntr < funcctx->max_calls)
		SRF_RETURN_NEXT(funcctx, result_set[call_cntr]->table_id);
	else /* do when there is no more left */
		SRF_RETURN_DONE(funcctx);
}