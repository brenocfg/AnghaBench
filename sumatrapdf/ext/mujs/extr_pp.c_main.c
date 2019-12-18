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
 int /*<<< orphan*/  js_freestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * js_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_ppfile (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  js_report (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_trystring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
main(int argc, char **argv)
{
	js_State *J;
	int minify = 0;
	int i;

	J = js_newstate(NULL, NULL, 0);

	for (i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-m"))
			minify = 1;
		else if (!strcmp(argv[i], "-mm"))
			minify = 2;
		else if (!strcmp(argv[i], "-s"))
			minify = 3;
		else {
			if (js_try(J)) {
				js_report(J, js_trystring(J, -1, "Error"));
				js_pop(J, 1);
				continue;
			}
			js_ppfile(J, argv[i], minify);
			js_endtry(J);
		}
	}

	js_gc(J, 0);
	js_freestate(J);

	return 0;
}