#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* source; char lexchar; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int TK_NUMBER ; 
 scalar_t__ jsY_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsY_error (TYPE_1__*,char*) ; 
 scalar_t__ jsY_isdec (char) ; 
 scalar_t__ jsY_isidentifierstart (char) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 
 int /*<<< orphan*/  js_strtod (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lexhex (TYPE_1__*) ; 

__attribute__((used)) static int lexnumber(js_State *J)
{
	const char *s = J->source - 1;

	if (jsY_accept(J, '0')) {
		if (jsY_accept(J, 'x') || jsY_accept(J, 'X')) {
			J->number = lexhex(J);
			return TK_NUMBER;
		}
		if (jsY_isdec(J->lexchar))
			jsY_error(J, "number with leading zero");
		if (jsY_accept(J, '.')) {
			while (jsY_isdec(J->lexchar))
				jsY_next(J);
		}
	} else if (jsY_accept(J, '.')) {
		if (!jsY_isdec(J->lexchar))
			return '.';
		while (jsY_isdec(J->lexchar))
			jsY_next(J);
	} else {
		while (jsY_isdec(J->lexchar))
			jsY_next(J);
		if (jsY_accept(J, '.')) {
			while (jsY_isdec(J->lexchar))
				jsY_next(J);
		}
	}

	if (jsY_accept(J, 'e') || jsY_accept(J, 'E')) {
		if (J->lexchar == '-' || J->lexchar == '+')
			jsY_next(J);
		if (jsY_isdec(J->lexchar))
			while (jsY_isdec(J->lexchar))
				jsY_next(J);
		else
			jsY_error(J, "missing exponent");
	}

	if (jsY_isidentifierstart(J->lexchar))
		jsY_error(J, "number with letter suffix");

	J->number = js_strtod(s, NULL);
	return TK_NUMBER;
}