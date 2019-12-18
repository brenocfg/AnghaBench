#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  tracetop; } ;
typedef  TYPE_4__ js_State ;
struct TYPE_22__ {int /*<<< orphan*/  function; int /*<<< orphan*/  length; int /*<<< orphan*/  name; } ;
struct TYPE_21__ {int /*<<< orphan*/  scope; TYPE_14__* function; } ;
struct TYPE_23__ {TYPE_2__ c; TYPE_1__ f; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_5__ js_Object ;
struct TYPE_20__ {char* filename; int /*<<< orphan*/  line; int /*<<< orphan*/  name; scalar_t__ lightweight; } ;

/* Variables and functions */
 int BOT ; 
 scalar_t__ JS_CCFUNCTION ; 
 scalar_t__ JS_CFUNCTION ; 
 scalar_t__ JS_CSCRIPT ; 
 int TOP ; 
 int /*<<< orphan*/  jsR_callcfunction (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsR_callfunction (TYPE_4__*,int,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsR_calllwfunction (TYPE_4__*,int,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsR_callscript (TYPE_4__*,int,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsR_pushtrace (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_iscallable (TYPE_4__*,int) ; 
 TYPE_5__* js_toobject (TYPE_4__*,int) ; 
 int /*<<< orphan*/  js_typeerror (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_typeof (TYPE_4__*,int) ; 

void js_call(js_State *J, int n)
{
	js_Object *obj;
	int savebot;

	if (!js_iscallable(J, -n-2))
		js_typeerror(J, "%s is not callable", js_typeof(J, -n-2));

	obj = js_toobject(J, -n-2);

	savebot = BOT;
	BOT = TOP - n - 1;

	if (obj->type == JS_CFUNCTION) {
		jsR_pushtrace(J, obj->u.f.function->name, obj->u.f.function->filename, obj->u.f.function->line);
		if (obj->u.f.function->lightweight)
			jsR_calllwfunction(J, n, obj->u.f.function, obj->u.f.scope);
		else
			jsR_callfunction(J, n, obj->u.f.function, obj->u.f.scope);
		--J->tracetop;
	} else if (obj->type == JS_CSCRIPT) {
		jsR_pushtrace(J, obj->u.f.function->name, obj->u.f.function->filename, obj->u.f.function->line);
		jsR_callscript(J, n, obj->u.f.function, obj->u.f.scope);
		--J->tracetop;
	} else if (obj->type == JS_CCFUNCTION) {
		jsR_pushtrace(J, obj->u.c.name, "native", 0);
		jsR_callcfunction(J, n, obj->u.c.length, obj->u.c.function);
		--J->tracetop;
	}

	BOT = savebot;
}