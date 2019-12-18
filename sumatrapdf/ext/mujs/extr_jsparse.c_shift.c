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
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 int /*<<< orphan*/  SHL ; 
 int /*<<< orphan*/  SHR ; 
 int /*<<< orphan*/  TK_SHL ; 
 int /*<<< orphan*/  TK_SHR ; 
 int /*<<< orphan*/  TK_USHR ; 
 int /*<<< orphan*/  USHR ; 
 int /*<<< orphan*/ * additive (TYPE_1__*) ; 
 scalar_t__ jsP_accept (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static js_Ast *shift(js_State *J)
{
	js_Ast *a = additive(J);
	int line;
	SAVEREC();
loop:
	INCREC();
	line = J->lexline;
	if (jsP_accept(J, TK_SHL)) { a = EXP2(SHL, a, additive(J)); goto loop; }
	if (jsP_accept(J, TK_SHR)) { a = EXP2(SHR, a, additive(J)); goto loop; }
	if (jsP_accept(J, TK_USHR)) { a = EXP2(USHR, a, additive(J)); goto loop; }
	POPREC();
	return a;
}