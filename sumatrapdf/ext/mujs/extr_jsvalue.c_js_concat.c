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
 int /*<<< orphan*/  JS_HNONE ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ js_isstring (int /*<<< orphan*/ *,int) ; 
 char* js_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_toprimitive (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void js_concat(js_State *J)
{
	js_toprimitive(J, -2, JS_HNONE);
	js_toprimitive(J, -1, JS_HNONE);

	if (js_isstring(J, -2) || js_isstring(J, -1)) {
		const char *sa = js_tostring(J, -2);
		const char *sb = js_tostring(J, -1);
		/* TODO: create js_String directly */
		char *sab = js_malloc(J, strlen(sa) + strlen(sb) + 1);
		strcpy(sab, sa);
		strcat(sab, sb);
		if (js_try(J)) {
			js_free(J, sab);
			js_throw(J);
		}
		js_pop(J, 2);
		js_pushstring(J, sab);
		js_endtry(J);
		js_free(J, sab);
	} else {
		double x = js_tonumber(J, -2);
		double y = js_tonumber(J, -1);
		js_pop(J, 2);
		js_pushnumber(J, x + y);
	}
}