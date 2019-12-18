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
struct TYPE_5__ {int lookahead; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,int) ; 

__attribute__((used)) static js_Ast *forexpression(js_State *J, int end)
{
	js_Ast *a = NULL;
	if (J->lookahead != end)
		a = expression(J, 0);
	jsP_expect(J, end);
	return a;
}