#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Put ;
struct TYPE_8__ {char const* tag; int /*<<< orphan*/  finalize; int /*<<< orphan*/  delete; int /*<<< orphan*/  put; int /*<<< orphan*/  has; void* data; } ;
struct TYPE_9__ {TYPE_1__ user; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
typedef  TYPE_3__ js_Object ;
typedef  int /*<<< orphan*/  js_HasProperty ;
typedef  int /*<<< orphan*/  js_Finalize ;
typedef  int /*<<< orphan*/  js_Delete ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CUSERDATA ; 
 TYPE_3__* jsV_newobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushobject (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* js_toobject (int /*<<< orphan*/ *,int) ; 

void js_newuserdatax(js_State *J, const char *tag, void *data, js_HasProperty has, js_Put put, js_Delete delete, js_Finalize finalize)
{
	js_Object *prototype = NULL;
	js_Object *obj;

	if (js_isobject(J, -1))
		prototype = js_toobject(J, -1);
	js_pop(J, 1);

	obj = jsV_newobject(J, JS_CUSERDATA, prototype);
	obj->u.user.tag = tag;
	obj->u.user.data = data;
	obj->u.user.has = has;
	obj->u.user.put = put;
	obj->u.user.delete = delete;
	obj->u.user.finalize = finalize;
	js_pushobject(J, obj);
}