#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lexchar; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 scalar_t__ jsY_accept (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  jsY_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  jsY_ishex (int) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 
 int jsY_tohex (int) ; 

__attribute__((used)) static void jsY_unescape(js_State *J)
{
	if (jsY_accept(J, '\\')) {
		if (jsY_accept(J, 'u')) {
			int x = 0;
			if (!jsY_ishex(J->lexchar)) { goto error; } x |= jsY_tohex(J->lexchar) << 12; jsY_next(J);
			if (!jsY_ishex(J->lexchar)) { goto error; } x |= jsY_tohex(J->lexchar) << 8; jsY_next(J);
			if (!jsY_ishex(J->lexchar)) { goto error; } x |= jsY_tohex(J->lexchar) << 4; jsY_next(J);
			if (!jsY_ishex(J->lexchar)) { goto error; } x |= jsY_tohex(J->lexchar);
			J->lexchar = x;
			return;
		}
error:
		jsY_error(J, "unexpected escape sequence");
	}
}