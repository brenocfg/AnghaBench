#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_15__ {int /*<<< orphan*/  root; } ;
struct TYPE_12__ {void* numeric; } ;
struct TYPE_14__ {TYPE_1__ val; void* type; } ;
struct TYPE_13__ {scalar_t__ len; char* data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  TYPE_4__ Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BGW_EXTRALEN ; 
 void* DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonbToCString (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* JsonbValueToJsonb (TYPE_3__*) ; 
 int /*<<< orphan*/  VARSIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  WJB_BEGIN_ARRAY ; 
 int /*<<< orphan*/  WJB_ELEM ; 
 int /*<<< orphan*/  WJB_END_ARRAY ; 
 int /*<<< orphan*/  int4_numeric ; 
 void* jbvNumeric ; 
 TYPE_2__* makeStringInfo () ; 
 TYPE_3__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static char *
serialize_test_parameters(int32 ttl)
{
	JsonbValue *result;
	JsonbValue ttl_value;
	JsonbParseState *parseState = NULL;
	Jsonb *jb;
	StringInfo jtext = makeStringInfo();
	JsonbValue user_oid;

	user_oid.type = jbvNumeric;
	user_oid.val.numeric =
		DatumGetNumeric(DirectFunctionCall1(int4_numeric, Int32GetDatum((int32) GetUserId())));

	ttl_value.type = jbvNumeric;
	ttl_value.val.numeric = DatumGetNumeric(DirectFunctionCall1(int4_numeric, Int32GetDatum(ttl)));

	result = pushJsonbValue(&parseState, WJB_BEGIN_ARRAY, NULL);

	result = pushJsonbValue(&parseState, WJB_ELEM, &ttl_value);
	result = pushJsonbValue(&parseState, WJB_ELEM, &user_oid);

	result = pushJsonbValue(&parseState, WJB_END_ARRAY, NULL);

	jb = JsonbValueToJsonb(result);
	(void) JsonbToCString(jtext, &jb->root, VARSIZE(jb));
	Assert(jtext->len < BGW_EXTRALEN);

	return jtext->data;
}