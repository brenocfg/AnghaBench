#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_12__ {TYPE_9__* target; TYPE_6__* head; } ;
struct TYPE_13__ {TYPE_3__ iter; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_4__ u; } ;
typedef  TYPE_5__ js_Object ;
struct TYPE_15__ {char* name; struct TYPE_15__* next; } ;
typedef  TYPE_6__ js_Iterator ;
struct TYPE_10__ {int length; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ JS_CITERATOR ; 
 scalar_t__ JS_CSTRING ; 
 scalar_t__ jsV_getproperty (int /*<<< orphan*/ *,TYPE_9__*,char const*) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ js_isarrayindex (int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

const char *jsV_nextiterator(js_State *J, js_Object *io)
{
	int k;
	if (io->type != JS_CITERATOR)
		js_typeerror(J, "not an iterator");
	while (io->u.iter.head) {
		js_Iterator *next = io->u.iter.head->next;
		const char *name = io->u.iter.head->name;
		js_free(J, io->u.iter.head);
		io->u.iter.head = next;
		if (jsV_getproperty(J, io->u.iter.target, name))
			return name;
		if (io->u.iter.target->type == JS_CSTRING)
			if (js_isarrayindex(J, name, &k) && k < io->u.iter.target->u.s.length)
				return name;
	}
	return NULL;
}