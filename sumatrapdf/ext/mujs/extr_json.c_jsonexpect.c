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

/* Variables and functions */
 int /*<<< orphan*/  jsY_tokenstring (int) ; 
 int /*<<< orphan*/  js_syntaxerror (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonaccept (TYPE_1__*,int) ; 

__attribute__((used)) static void jsonexpect(js_State *J, int t)
{
	if (!jsonaccept(J, t))
		js_syntaxerror(J, "JSON: unexpected token: %s (expected %s)",
				jsY_tokenstring(J->lookahead), jsY_tokenstring(t));
}