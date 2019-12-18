#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_7__ {int /*<<< orphan*/  root; } ;
struct TYPE_5__ {int /*<<< orphan*/  numeric; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Numeric ;
typedef  TYPE_2__ JsonbValue ;
typedef  TYPE_3__ Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 TYPE_2__* getIthJsonbValueFromContainer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jbvNumeric ; 
 int /*<<< orphan*/  jsonb_in ; 
 int /*<<< orphan*/  numeric_int4 ; 

__attribute__((used)) static void
deserialize_test_parameters(char *params, int32 *ttl, Oid *user_oid)
{
	Jsonb *jb = (Jsonb *) DatumGetPointer(DirectFunctionCall1(jsonb_in, CStringGetDatum(params)));
	JsonbValue *ttl_v = getIthJsonbValueFromContainer(&jb->root, 0);
	JsonbValue *user_v = getIthJsonbValueFromContainer(&jb->root, 1);
	Numeric ttl_numeric;
	Numeric user_numeric;

	Assert(ttl_v->type == jbvNumeric);
	Assert(user_v->type == jbvNumeric);

	ttl_numeric = ttl_v->val.numeric;
	user_numeric = user_v->val.numeric;
	*ttl = DatumGetInt32(DirectFunctionCall1(numeric_int4, NumericGetDatum(ttl_numeric)));
	*user_oid =
		(Oid) DatumGetInt32(DirectFunctionCall1(numeric_int4, NumericGetDatum(user_numeric)));
}