#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int tracetop; TYPE_1__* trace; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_6__ {char* name; char* file; int line; } ;

/* Variables and functions */
 int /*<<< orphan*/  js_concat (TYPE_2__*) ; 
 int /*<<< orphan*/  js_pushstring (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

__attribute__((used)) static int jsB_stacktrace(js_State *J, int skip)
{
	char buf[256];
	int n = J->tracetop - skip;
	if (n <= 0)
		return 0;
	for (; n > 0; --n) {
		const char *name = J->trace[n].name;
		const char *file = J->trace[n].file;
		int line = J->trace[n].line;
		if (line > 0) {
			if (name[0])
				snprintf(buf, sizeof buf, "\n\tat %s (%s:%d)", name, file, line);
			else
				snprintf(buf, sizeof buf, "\n\tat %s:%d", file, line);
		} else
			snprintf(buf, sizeof buf, "\n\tat %s (%s)", name, file);
		js_pushstring(J, buf);
		if (n < J->tracetop - skip)
			js_concat(J);
	}
	return 1;
}