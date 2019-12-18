#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  BITNOT ; 
 int /*<<< orphan*/  DECREC () ; 
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/ * EXP1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  LOGNOT ; 
 int /*<<< orphan*/  NEG ; 
 int /*<<< orphan*/  POS ; 
 int /*<<< orphan*/  PREDEC ; 
 int /*<<< orphan*/  PREINC ; 
 char TK_DEC ; 
 char TK_DELETE ; 
 char TK_INC ; 
 char TK_TYPEOF ; 
 char TK_VOID ; 
 int /*<<< orphan*/  TYPEOF ; 
 int /*<<< orphan*/  VOID ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * postfix (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *unary(js_State *J)
{
	js_Ast *a;
	int line = J->lexline;
	INCREC();
	if (jsP_accept(J, TK_DELETE)) a = EXP1(DELETE, unary(J));
	else if (jsP_accept(J, TK_VOID)) a = EXP1(VOID, unary(J));
	else if (jsP_accept(J, TK_TYPEOF)) a = EXP1(TYPEOF, unary(J));
	else if (jsP_accept(J, TK_INC)) a = EXP1(PREINC, unary(J));
	else if (jsP_accept(J, TK_DEC)) a = EXP1(PREDEC, unary(J));
	else if (jsP_accept(J, '+')) a = EXP1(POS, unary(J));
	else if (jsP_accept(J, '-')) a = EXP1(NEG, unary(J));
	else if (jsP_accept(J, '~')) a = EXP1(BITNOT, unary(J));
	else if (jsP_accept(J, '!')) a = EXP1(LOGNOT, unary(J));
	else a = postfix(J);
	DECREC();
	return a;
}