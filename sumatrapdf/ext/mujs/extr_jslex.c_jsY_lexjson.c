#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char lexchar; int /*<<< orphan*/  line; int /*<<< orphan*/  lexline; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int TK_FALSE ; 
 int TK_NULL ; 
 int TK_TRUE ; 
 int /*<<< orphan*/  jsY_error (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  jsY_expect (TYPE_1__*,char) ; 
 scalar_t__ jsY_iswhite (char) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 
 int lexjsonnumber (TYPE_1__*) ; 
 int lexjsonstring (TYPE_1__*) ; 

int jsY_lexjson(js_State *J)
{
	while (1) {
		J->lexline = J->line; /* save location of beginning of token */

		while (jsY_iswhite(J->lexchar) || J->lexchar == '\n')
			jsY_next(J);

		if ((J->lexchar >= '0' && J->lexchar <= '9') || J->lexchar == '-')
			return lexjsonnumber(J);

		switch (J->lexchar) {
		case ',': jsY_next(J); return ',';
		case ':': jsY_next(J); return ':';
		case '[': jsY_next(J); return '[';
		case ']': jsY_next(J); return ']';
		case '{': jsY_next(J); return '{';
		case '}': jsY_next(J); return '}';

		case '"':
			jsY_next(J);
			return lexjsonstring(J);

		case 'f':
			jsY_next(J); jsY_expect(J, 'a'); jsY_expect(J, 'l'); jsY_expect(J, 's'); jsY_expect(J, 'e');
			return TK_FALSE;

		case 'n':
			jsY_next(J); jsY_expect(J, 'u'); jsY_expect(J, 'l'); jsY_expect(J, 'l');
			return TK_NULL;

		case 't':
			jsY_next(J); jsY_expect(J, 'r'); jsY_expect(J, 'u'); jsY_expect(J, 'e');
			return TK_TRUE;

		case 0:
			return 0; /* EOF */
		}

		if (J->lexchar >= 0x20 && J->lexchar <= 0x7E)
			jsY_error(J, "unexpected character: '%c'", J->lexchar);
		jsY_error(J, "unexpected character: \\u%04X", J->lexchar);
	}
}