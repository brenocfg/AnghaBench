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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_ploadstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 char* js_tryrepr (int /*<<< orphan*/ *,int,char*) ; 
 char* js_trystring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int eval_print(js_State *J, const char *source)
{
	if (js_ploadstring(J, "[stdin]", source)) {
		fprintf(stderr, "%s\n", js_trystring(J, -1, "Error"));
		js_pop(J, 1);
		return 1;
	}
	js_pushundefined(J);
	if (js_pcall(J, 0)) {
		fprintf(stderr, "%s\n", js_trystring(J, -1, "Error"));
		js_pop(J, 1);
		return 1;
	}
	if (js_isdefined(J, -1)) {
		printf("%s\n", js_tryrepr(J, -1, "can't convert to string"));
	}
	js_pop(J, 1);
	return 0;
}