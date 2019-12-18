#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int lexline; scalar_t__ lookahead; int /*<<< orphan*/  number; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_20__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY ; 
 TYPE_2__* EXP0 (int /*<<< orphan*/ *) ; 
 TYPE_2__* EXP1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXP_IDENTIFIER ; 
 int /*<<< orphan*/  EXP_NUMBER ; 
 int /*<<< orphan*/  EXP_REGEXP ; 
 int /*<<< orphan*/  EXP_STRING ; 
 int /*<<< orphan*/ * FALSE ; 
 int /*<<< orphan*/  OBJECT ; 
 int /*<<< orphan*/ * THIS ; 
 char TK_FALSE ; 
 scalar_t__ TK_IDENTIFIER ; 
 char TK_NULL ; 
 scalar_t__ TK_NUMBER ; 
 scalar_t__ TK_REGEXP ; 
 scalar_t__ TK_STRING ; 
 char TK_THIS ; 
 char TK_TRUE ; 
 int /*<<< orphan*/ * TRUE ; 
 int /*<<< orphan*/  arrayliteral (TYPE_1__*) ; 
 TYPE_2__* expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 TYPE_2__* jsP_newnumnode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* jsP_newstrnode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_next (TYPE_1__*) ; 
 int /*<<< orphan*/  jsY_tokenstring (scalar_t__) ; 
 int /*<<< orphan*/  objectliteral (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *primary(js_State *J)
{
	js_Ast *a;
	int line = J->lexline;

	if (J->lookahead == TK_IDENTIFIER) {
		a = jsP_newstrnode(J, EXP_IDENTIFIER, J->text);
		jsP_next(J);
		return a;
	}
	if (J->lookahead == TK_STRING) {
		a = jsP_newstrnode(J, EXP_STRING, J->text);
		jsP_next(J);
		return a;
	}
	if (J->lookahead == TK_REGEXP) {
		a = jsP_newstrnode(J, EXP_REGEXP, J->text);
		a->number = J->number;
		jsP_next(J);
		return a;
	}
	if (J->lookahead == TK_NUMBER) {
		a = jsP_newnumnode(J, EXP_NUMBER, J->number);
		jsP_next(J);
		return a;
	}

	if (jsP_accept(J, TK_THIS)) return EXP0(THIS);
	if (jsP_accept(J, TK_NULL)) return EXP0(NULL);
	if (jsP_accept(J, TK_TRUE)) return EXP0(TRUE);
	if (jsP_accept(J, TK_FALSE)) return EXP0(FALSE);
	if (jsP_accept(J, '{')) {
		a = EXP1(OBJECT, objectliteral(J));
		jsP_expect(J, '}');
		return a;
	}
	if (jsP_accept(J, '[')) {
		a = EXP1(ARRAY, arrayliteral(J));
		jsP_expect(J, ']');
		return a;
	}
	if (jsP_accept(J, '(')) {
		a = expression(J, 0);
		jsP_expect(J, ')');
		return a;
	}

	jsP_error(J, "unexpected token in expression: %s", jsY_tokenstring(J->lookahead));
}