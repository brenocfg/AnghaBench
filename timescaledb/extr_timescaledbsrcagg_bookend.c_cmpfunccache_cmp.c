#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ cmp_type; char op; int /*<<< orphan*/  proc; } ;
struct TYPE_11__ {int /*<<< orphan*/  fncollation; TYPE_1__* flinfo; } ;
struct TYPE_10__ {scalar_t__ type_oid; int /*<<< orphan*/  datum; } ;
struct TYPE_9__ {int /*<<< orphan*/  fn_mcxt; } ;
typedef  TYPE_2__ PolyDatum ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__* FunctionCallInfo ;
typedef  TYPE_4__ CmpFuncCache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 scalar_t__ OpernameGetOprid (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fmgr_info_cxt (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_opcode (scalar_t__) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 

__attribute__((used)) inline static bool
cmpfunccache_cmp(CmpFuncCache *cache, FunctionCallInfo fcinfo, char *opname, PolyDatum left,
				 PolyDatum right)
{
	Assert(left.type_oid == right.type_oid);
	Assert(opname[1] == '\0');

	if (cache->cmp_type != left.type_oid || cache->op != opname[0])
	{
		Oid cmp_op, cmp_regproc;

		if (!OidIsValid(left.type_oid))
			elog(ERROR, "could not determine the type of the comparison_element");
		cmp_op = OpernameGetOprid(list_make1(makeString(opname)), left.type_oid, left.type_oid);
		if (!OidIsValid(cmp_op))
			elog(ERROR, "could not find a %s operator for type %d", opname, left.type_oid);
		cmp_regproc = get_opcode(cmp_op);
		if (!OidIsValid(cmp_regproc))
			elog(ERROR,
				 "could not find the procedure for the %s operator for type %d",
				 opname,
				 left.type_oid);
		fmgr_info_cxt(cmp_regproc, &cache->proc, fcinfo->flinfo->fn_mcxt);
	}
	return DatumGetBool(
		FunctionCall2Coll(&cache->proc, fcinfo->fncollation, left.datum, right.datum));
}