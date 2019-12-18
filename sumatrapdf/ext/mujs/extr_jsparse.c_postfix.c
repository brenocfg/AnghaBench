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
struct TYPE_5__ {int lexline; int /*<<< orphan*/  newline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * EXP1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POSTDEC ; 
 int /*<<< orphan*/  POSTINC ; 
 int /*<<< orphan*/  TK_DEC ; 
 int /*<<< orphan*/  TK_INC ; 
 int /*<<< orphan*/ * callexp (TYPE_1__*) ; 
 scalar_t__ jsP_accept (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static js_Ast *postfix(js_State *J)
{
	js_Ast *a = callexp(J);
	int line = J->lexline;
	if (!J->newline && jsP_accept(J, TK_INC)) return EXP1(POSTINC, a);
	if (!J->newline && jsP_accept(J, TK_DEC)) return EXP1(POSTDEC, a);
	return a;
}