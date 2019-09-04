#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WJB_KEY ; 
 int /*<<< orphan*/  WJB_VALUE ; 
 int /*<<< orphan*/  pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ts_jsonb_add_pair(JsonbParseState *state, JsonbValue *key, JsonbValue *value)
{
	Assert(state != NULL);
	Assert(key != NULL);
	if (value == NULL)
		return;

	pushJsonbValue(&state, WJB_KEY, key);
	pushJsonbValue(&state, WJB_VALUE, value);
}