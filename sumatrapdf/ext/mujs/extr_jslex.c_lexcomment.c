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
struct TYPE_5__ {scalar_t__ lexchar; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 scalar_t__ jsY_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 

__attribute__((used)) static int lexcomment(js_State *J)
{
	/* already consumed initial '/' '*' sequence */
	while (J->lexchar != 0) {
		if (jsY_accept(J, '*')) {
			while (J->lexchar == '*')
				jsY_next(J);
			if (jsY_accept(J, '/'))
				return 0;
		}
		else
			jsY_next(J);
	}
	return -1;
}