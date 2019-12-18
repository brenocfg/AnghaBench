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
 double INFINITY ; 
 double NAN ; 
 scalar_t__ jsY_isnewline (char const) ; 
 scalar_t__ jsY_iswhite (char const) ; 
 double js_stringtofloat (char const*,char**) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 double strtol (char const*,char**,int) ; 

double jsV_stringtonumber(js_State *J, const char *s)
{
	char *e;
	double n;
	while (jsY_iswhite(*s) || jsY_isnewline(*s)) ++s;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X') && s[2] != 0)
		n = strtol(s + 2, &e, 16);
	else if (!strncmp(s, "Infinity", 8))
		n = INFINITY, e = (char*)s + 8;
	else if (!strncmp(s, "+Infinity", 9))
		n = INFINITY, e = (char*)s + 9;
	else if (!strncmp(s, "-Infinity", 9))
		n = -INFINITY, e = (char*)s + 9;
	else
		n = js_stringtofloat(s, &e);
	while (jsY_iswhite(*e) || jsY_isnewline(*e)) ++e;
	if (*e) return NAN;
	return n;
}