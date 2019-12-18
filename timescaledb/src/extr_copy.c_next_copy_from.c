#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cstate; } ;
struct TYPE_5__ {TYPE_1__ fromctx; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ CopyChunkState ;

/* Variables and functions */
 int NextCopyFrom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
next_copy_from(CopyChunkState *ccstate, ExprContext *econtext, Datum *values, bool *nulls,
			   Oid *tuple_oid)
{
	return NextCopyFrom(ccstate->fromctx.cstate, econtext, values, nulls, tuple_oid);
}