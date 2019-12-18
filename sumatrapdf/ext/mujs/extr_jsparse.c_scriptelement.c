#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  TK_FUNCTION ; 
 int /*<<< orphan*/ * fundec (TYPE_1__*,int) ; 
 scalar_t__ jsP_accept (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * statement (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *scriptelement(js_State *J)
{
	int line = J->lexline;
	if (jsP_accept(J, TK_FUNCTION))
		return fundec(J, line);
	return statement(J);
}