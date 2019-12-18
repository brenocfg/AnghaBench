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
struct TYPE_5__ {int /*<<< orphan*/  lexchar; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  jsY_error (TYPE_1__*,char*) ; 
 scalar_t__ jsY_ishex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 
 double jsY_tohex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double lexhex(js_State *J)
{
	double n = 0;
	if (!jsY_ishex(J->lexchar))
		jsY_error(J, "malformed hexadecimal number");
	while (jsY_ishex(J->lexchar)) {
		n = n * 16 + jsY_tohex(J->lexchar);
		jsY_next(J);
	}
	return n;
}