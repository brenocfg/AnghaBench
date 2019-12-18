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
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {char* s; } ;
typedef  TYPE_1__ js_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fmtvalue (int /*<<< orphan*/ *,TYPE_1__**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_defproperty (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ js_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_rot2pop1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void JSON_stringify(js_State *J)
{
	js_Buffer *sb = NULL;
	char buf[12];
	const char *s, *gap;
	int n;

	gap = NULL;

	if (js_isnumber(J, 3)) {
		n = js_tointeger(J, 3);
		if (n < 0) n = 0;
		if (n > 10) n = 10;
		memset(buf, ' ', n);
		buf[n] = 0;
		if (n > 0) gap = buf;
	} else if (js_isstring(J, 3)) {
		s = js_tostring(J, 3);
		n = strlen(s);
		if (n > 10) n = 10;
		memcpy(buf, s, n);
		buf[n] = 0;
		if (n > 0) gap = buf;
	}

	if (js_try(J)) {
		js_free(J, sb);
		js_throw(J);
	}

	js_newobject(J); /* wrapper */
	js_copy(J, 1);
	js_defproperty(J, -2, "", 0);
	if (!fmtvalue(J, &sb, "", gap, 0)) {
		js_pushundefined(J);
	} else {
		js_putc(J, &sb, 0);
		js_pushstring(J, sb ? sb->s : "");
		js_rot2pop1(J);
	}

	js_endtry(J);
	js_free(J, sb);
}