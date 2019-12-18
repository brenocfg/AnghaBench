#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tracetop; TYPE_1__* trace; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_5__ {char const* name; char const* file; int line; } ;

/* Variables and functions */
 int JS_ENVLIMIT ; 
 int /*<<< orphan*/  js_error (TYPE_2__*,char*) ; 

__attribute__((used)) static void jsR_pushtrace(js_State *J, const char *name, const char *file, int line)
{
	if (J->tracetop + 1 == JS_ENVLIMIT)
		js_error(J, "call stack overflow");
	++J->tracetop;
	J->trace[J->tracetop].name = name;
	J->trace[J->tracetop].file = file;
	J->trace[J->tracetop].line = line;
}