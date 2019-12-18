#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* filename; char const* source; int line; scalar_t__ lasttoken; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 

void jsY_initlex(js_State *J, const char *filename, const char *source)
{
	J->filename = filename;
	J->source = source;
	J->line = 1;
	J->lasttoken = 0;
	jsY_next(J); /* load first lookahead character */
}