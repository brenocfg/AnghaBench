#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  INDEX ; 
 int /*<<< orphan*/  MEMBER ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 int /*<<< orphan*/  arguments (TYPE_1__*) ; 
 int /*<<< orphan*/  expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identifiername (TYPE_1__*) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * newexp (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *callexp(js_State *J)
{
	js_Ast *a = newexp(J);
	int line;
	SAVEREC();
loop:
	INCREC();
	line = J->lexline;
	if (jsP_accept(J, '.')) { a = EXP2(MEMBER, a, identifiername(J)); goto loop; }
	if (jsP_accept(J, '[')) { a = EXP2(INDEX, a, expression(J, 0)); jsP_expect(J, ']'); goto loop; }
	if (jsP_accept(J, '(')) { a = EXP2(CALL, a, arguments(J)); jsP_expect(J, ')'); goto loop; }
	POPREC();
	return a;
}