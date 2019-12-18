#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int bot; int top; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_17__ {char* s; } ;
typedef  TYPE_2__ js_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  js_copy (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_endtry (TYPE_1__*) ; 
 int /*<<< orphan*/  js_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  js_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_pushstring (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  js_putc (TYPE_1__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_throw (TYPE_1__*) ; 
 scalar_t__ js_try (TYPE_1__*) ; 
 int /*<<< orphan*/  reprvalue (TYPE_1__*,TYPE_2__**) ; 

void js_repr(js_State *J, int idx)
{
	js_Buffer *sb = NULL;
	int savebot;

	if (js_try(J)) {
		js_free(J, sb);
		js_throw(J);
	}

	js_copy(J, idx);

	savebot = J->bot;
	J->bot = J->top - 1;
	reprvalue(J, &sb);
	J->bot = savebot;

	js_pop(J, 1);

	js_putc(J, &sb, 0);
	js_pushstring(J, sb ? sb->s : "undefined");

	js_endtry(J);
	js_free(J, sb);
}