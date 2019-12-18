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
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  js_pushnull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* readline (char*) ; 

__attribute__((used)) static void jsB_readline(js_State *J)
{
	char *line = readline("");
	if (!line) {
		js_pushnull(J);
		return;
	}
	js_pushstring(J, line);
	if (*line)
		add_history(line);
	free(line);
}