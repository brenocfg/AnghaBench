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
 int /*<<< orphan*/  EQ ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  NE ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 int /*<<< orphan*/  STRICTEQ ; 
 int /*<<< orphan*/  STRICTNE ; 
 int /*<<< orphan*/  TK_EQ ; 
 int /*<<< orphan*/  TK_NE ; 
 int /*<<< orphan*/  TK_STRICTEQ ; 
 int /*<<< orphan*/  TK_STRICTNE ; 
 scalar_t__ jsP_accept (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * relational (TYPE_1__*,int) ; 

__attribute__((used)) static js_Ast *equality(js_State *J, int notin)
{
	js_Ast *a = relational(J, notin);
	int line;
	SAVEREC();
loop:
	INCREC();
	line = J->lexline;
	if (jsP_accept(J, TK_EQ)) { a = EXP2(EQ, a, relational(J, notin)); goto loop; }
	if (jsP_accept(J, TK_NE)) { a = EXP2(NE, a, relational(J, notin)); goto loop; }
	if (jsP_accept(J, TK_STRICTEQ)) { a = EXP2(STRICTEQ, a, relational(J, notin)); goto loop; }
	if (jsP_accept(J, TK_STRICTNE)) { a = EXP2(STRICTNE, a, relational(J, notin)); goto loop; }
	POPREC();
	return a;
}