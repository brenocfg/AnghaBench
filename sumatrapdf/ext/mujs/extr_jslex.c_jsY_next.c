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
struct TYPE_3__ {char* source; char lexchar; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ js_State ;
typedef  char Rune ;

/* Variables and functions */
 int /*<<< orphan*/  chartorune (char*,char*) ; 
 scalar_t__ jsY_isnewline (char) ; 

__attribute__((used)) static void jsY_next(js_State *J)
{
	Rune c;
	J->source += chartorune(&c, J->source);
	/* consume CR LF as one unit */
	if (c == '\r' && *J->source == '\n')
		++J->source;
	if (jsY_isnewline(c)) {
		J->line++;
		c = '\n';
	}
	J->lexchar = c;
}