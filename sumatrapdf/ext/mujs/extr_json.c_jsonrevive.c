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
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_delproperty (int /*<<< orphan*/ *,int,char const*) ; 
 int js_getlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ js_isarray (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 char* js_itoa (char*,int) ; 
 char* js_nextiterator (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushiterator (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_rot2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_rot2pop1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void jsonrevive(js_State *J, const char *name)
{
	const char *key;
	char buf[32];

	/* revive is in 2 */
	/* holder is in -1 */

	js_getproperty(J, -1, name); /* get value from holder */

	if (js_isobject(J, -1)) {
		if (js_isarray(J, -1)) {
			int i = 0;
			int n = js_getlength(J, -1);
			for (i = 0; i < n; ++i) {
				jsonrevive(J, js_itoa(buf, i));
				if (js_isundefined(J, -1)) {
					js_pop(J, 1);
					js_delproperty(J, -1, buf);
				} else {
					js_setproperty(J, -2, buf);
				}
			}
		} else {
			js_pushiterator(J, -1, 1);
			while ((key = js_nextiterator(J, -1))) {
				js_rot2(J);
				jsonrevive(J, key);
				if (js_isundefined(J, -1)) {
					js_pop(J, 1);
					js_delproperty(J, -1, key);
				} else {
					js_setproperty(J, -2, key);
				}
				js_rot2(J);
			}
			js_pop(J, 1);
		}
	}

	js_copy(J, 2); /* reviver function */
	js_copy(J, -3); /* holder as this */
	js_pushstring(J, name); /* name */
	js_copy(J, -4); /* value */
	js_call(J, 2);
	js_rot2pop1(J); /* pop old value, leave new value on stack */
}