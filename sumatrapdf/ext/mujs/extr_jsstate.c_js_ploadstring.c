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

/* Variables and functions */
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_loadstring (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

int js_ploadstring(js_State *J, const char *filename, const char *source)
{
	if (js_try(J))
		return 1;
	js_loadstring(J, filename, source);
	js_endtry(J);
	return 0;
}