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
struct TYPE_7__ {int lexchar; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 scalar_t__ jsY_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsY_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  jsY_ishex (int) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 
 int jsY_tohex (int) ; 
 int /*<<< orphan*/  textpush (TYPE_1__*,char) ; 

__attribute__((used)) static int lexescape(js_State *J)
{
	int x = 0;

	/* already consumed '\' */

	if (jsY_accept(J, '\n'))
		return 0;

	switch (J->lexchar) {
	case 0: jsY_error(J, "unterminated escape sequence");
	case 'u':
		jsY_next(J);
		if (!jsY_ishex(J->lexchar)) return 1; else { x |= jsY_tohex(J->lexchar) << 12; jsY_next(J); }
		if (!jsY_ishex(J->lexchar)) return 1; else { x |= jsY_tohex(J->lexchar) << 8; jsY_next(J); }
		if (!jsY_ishex(J->lexchar)) return 1; else { x |= jsY_tohex(J->lexchar) << 4; jsY_next(J); }
		if (!jsY_ishex(J->lexchar)) return 1; else { x |= jsY_tohex(J->lexchar); jsY_next(J); }
		textpush(J, x);
		break;
	case 'x':
		jsY_next(J);
		if (!jsY_ishex(J->lexchar)) return 1; else { x |= jsY_tohex(J->lexchar) << 4; jsY_next(J); }
		if (!jsY_ishex(J->lexchar)) return 1; else { x |= jsY_tohex(J->lexchar); jsY_next(J); }
		textpush(J, x);
		break;
	case '0': textpush(J, 0); jsY_next(J); break;
	case '\\': textpush(J, '\\'); jsY_next(J); break;
	case '\'': textpush(J, '\''); jsY_next(J); break;
	case '"': textpush(J, '"'); jsY_next(J); break;
	case 'b': textpush(J, '\b'); jsY_next(J); break;
	case 'f': textpush(J, '\f'); jsY_next(J); break;
	case 'n': textpush(J, '\n'); jsY_next(J); break;
	case 'r': textpush(J, '\r'); jsY_next(J); break;
	case 't': textpush(J, '\t'); jsY_next(J); break;
	case 'v': textpush(J, '\v'); jsY_next(J); break;
	default: textpush(J, J->lexchar); jsY_next(J); break;
	}
	return 0;
}