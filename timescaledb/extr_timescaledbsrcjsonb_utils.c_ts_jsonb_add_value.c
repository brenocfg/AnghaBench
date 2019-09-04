#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* val; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ string; } ;
struct TYPE_9__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvString ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  ts_jsonb_add_pair (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 

void
ts_jsonb_add_value(JsonbParseState *state, const char *key, JsonbValue *value)
{
	JsonbValue json_key;

	Assert(key != NULL);
	if (value == NULL)
		return;

	json_key.type = jbvString;
	json_key.val.string.val = (char *) key;
	json_key.val.string.len = strlen(key);

	ts_jsonb_add_pair(state, &json_key, value);
}