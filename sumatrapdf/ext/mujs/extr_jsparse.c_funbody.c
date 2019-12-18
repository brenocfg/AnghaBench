#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  jsP_expect (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * script (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static js_Ast *funbody(js_State *J)
{
	js_Ast *a;
	jsP_expect(J, '{');
	a = script(J, '}');
	jsP_expect(J, '}');
	return a;
}