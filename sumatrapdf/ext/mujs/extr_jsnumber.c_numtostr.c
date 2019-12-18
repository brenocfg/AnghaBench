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
 int atoi (char*) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int,...) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void numtostr(js_State *J, const char *fmt, int w, double n)
{
	/* buf needs to fit printf("%.20f", 1e20) */
	char buf[50], *e;
	sprintf(buf, fmt, w, n);
	e = strchr(buf, 'e');
	if (e) {
		int exp = atoi(e+1);
		sprintf(e, "e%+d", exp);
	}
	js_pushstring(J, buf);
}