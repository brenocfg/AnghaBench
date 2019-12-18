#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_16__ {TYPE_5__* head; TYPE_4__* target; } ;
struct TYPE_15__ {int length; } ;
struct TYPE_17__ {TYPE_2__ iter; TYPE_1__ s; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_3__ u; int /*<<< orphan*/ * properties; } ;
typedef  TYPE_4__ js_Object ;
struct TYPE_19__ {struct TYPE_19__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ js_Iterator ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CITERATOR ; 
 scalar_t__ JS_CSTRING ; 
 TYPE_5__* itflatten (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_5__* itwalk (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsV_getenumproperty (int /*<<< orphan*/ *,TYPE_4__*,char*) ; 
 TYPE_4__* jsV_newobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_intern (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_itoa (char*,int) ; 
 TYPE_5__* js_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sentinel ; 

js_Object *jsV_newiterator(js_State *J, js_Object *obj, int own)
{
	char buf[32];
	int k;
	js_Object *io = jsV_newobject(J, JS_CITERATOR, NULL);
	io->u.iter.target = obj;
	if (own) {
		io->u.iter.head = NULL;
		if (obj->properties != &sentinel)
			io->u.iter.head = itwalk(J, io->u.iter.head, obj->properties, NULL);
	} else {
		io->u.iter.head = itflatten(J, obj);
	}
	if (obj->type == JS_CSTRING) {
		js_Iterator *tail = io->u.iter.head;
		if (tail)
			while (tail->next)
				tail = tail->next;
		for (k = 0; k < obj->u.s.length; ++k) {
			js_itoa(buf, k);
			if (!jsV_getenumproperty(J, obj, buf)) {
				js_Iterator *node = js_malloc(J, sizeof *node);
				node->name = js_intern(J, js_itoa(buf, k));
				node->next = NULL;
				if (!tail)
					io->u.iter.head = tail = node;
				else {
					tail->next = node;
					tail = node;
				}
			}
		}
	}
	return io;
}