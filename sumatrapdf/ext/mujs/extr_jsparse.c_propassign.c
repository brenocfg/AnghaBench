#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int lexline; char lookahead; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_22__ {scalar_t__ type; int /*<<< orphan*/  string; } ;
typedef  TYPE_2__ js_Ast ;

/* Variables and functions */
 scalar_t__ AST_IDENTIFIER ; 
 TYPE_2__* EXP2 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* EXP3 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * LIST (TYPE_2__*) ; 
 int /*<<< orphan*/  PROP_GET ; 
 int /*<<< orphan*/  PROP_SET ; 
 int /*<<< orphan*/  PROP_VAL ; 
 TYPE_2__* assignment (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* funbody (TYPE_1__*) ; 
 TYPE_2__* identifier (TYPE_1__*) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 TYPE_2__* propname (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static js_Ast *propassign(js_State *J)
{
	js_Ast *name, *value, *arg, *body;
	int line = J->lexline;

	name = propname(J);

	if (J->lookahead != ':' && name->type == AST_IDENTIFIER) {
		if (!strcmp(name->string, "get")) {
			name = propname(J);
			jsP_expect(J, '(');
			jsP_expect(J, ')');
			body = funbody(J);
			return EXP3(PROP_GET, name, NULL, body);
		}
		if (!strcmp(name->string, "set")) {
			name = propname(J);
			jsP_expect(J, '(');
			arg = identifier(J);
			jsP_expect(J, ')');
			body = funbody(J);
			return EXP3(PROP_SET, name, LIST(arg), body);
		}
	}

	jsP_expect(J, ':');
	value = assignment(J, 0);
	return EXP2(PROP_VAL, name, value);
}