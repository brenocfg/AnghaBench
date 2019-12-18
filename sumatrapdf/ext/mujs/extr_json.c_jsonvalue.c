#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int lookahead; char* text; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
#define  TK_FALSE 132 
#define  TK_NULL 131 
#define  TK_NUMBER 130 
#define  TK_STRING 129 
#define  TK_TRUE 128 
 int /*<<< orphan*/  jsY_tokenstring (int const) ; 
 int /*<<< orphan*/  js_newarray (TYPE_1__*) ; 
 int /*<<< orphan*/  js_newobject (TYPE_1__*) ; 
 int /*<<< orphan*/  js_pushboolean (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_pushnull (TYPE_1__*) ; 
 int /*<<< orphan*/  js_pushnumber (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  js_setindex (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setproperty (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  js_syntaxerror (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonaccept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsonexpect (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsonnext (TYPE_1__*) ; 

__attribute__((used)) static void jsonvalue(js_State *J)
{
	int i;
	const char *name;

	switch (J->lookahead) {
	case TK_STRING:
		js_pushstring(J, J->text);
		jsonnext(J);
		break;

	case TK_NUMBER:
		js_pushnumber(J, J->number);
		jsonnext(J);
		break;

	case '{':
		js_newobject(J);
		jsonnext(J);
		if (jsonaccept(J, '}'))
			return;
		do {
			if (J->lookahead != TK_STRING)
				js_syntaxerror(J, "JSON: unexpected token: %s (expected string)", jsY_tokenstring(J->lookahead));
			name = J->text;
			jsonnext(J);
			jsonexpect(J, ':');
			jsonvalue(J);
			js_setproperty(J, -2, name);
		} while (jsonaccept(J, ','));
		jsonexpect(J, '}');
		break;

	case '[':
		js_newarray(J);
		jsonnext(J);
		i = 0;
		if (jsonaccept(J, ']'))
			return;
		do {
			jsonvalue(J);
			js_setindex(J, -2, i++);
		} while (jsonaccept(J, ','));
		jsonexpect(J, ']');
		break;

	case TK_TRUE:
		js_pushboolean(J, 1);
		jsonnext(J);
		break;

	case TK_FALSE:
		js_pushboolean(J, 0);
		jsonnext(J);
		break;

	case TK_NULL:
		js_pushnull(J);
		jsonnext(J);
		break;

	default:
		js_syntaxerror(J, "JSON: unexpected token: %s", jsY_tokenstring(J->lookahead));
	}
}