#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {char* source; int flags; } ;
typedef  TYPE_1__ js_Regexp ;

/* Variables and functions */
 int JS_REGEXP_G ; 
 int JS_REGEXP_I ; 
 int JS_REGEXP_M ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,char*) ; 
 char* js_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 TYPE_1__* js_toregexp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void Rp_toString(js_State *J)
{
	js_Regexp *re;
	char *out;

	re = js_toregexp(J, 0);

	out = js_malloc(J, strlen(re->source) + 6); /* extra space for //gim */
	strcpy(out, "/");
	strcat(out, re->source);
	strcat(out, "/");
	if (re->flags & JS_REGEXP_G) strcat(out, "g");
	if (re->flags & JS_REGEXP_I) strcat(out, "i");
	if (re->flags & JS_REGEXP_M) strcat(out, "m");

	if (js_try(J)) {
		js_free(J, out);
		js_throw(J);
	}
	js_pop(J, 0);
	js_pushstring(J, out);
	js_endtry(J);
	js_free(J, out);
}