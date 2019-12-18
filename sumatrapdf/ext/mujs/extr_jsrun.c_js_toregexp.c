#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* object; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_4__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Regexp ;
struct TYPE_6__ {int /*<<< orphan*/  r; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ JS_CREGEXP ; 
 scalar_t__ JS_TOBJECT ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* stackidx (int /*<<< orphan*/ *,int) ; 

js_Regexp *js_toregexp(js_State *J, int idx)
{
	js_Value *v = stackidx(J, idx);
	if (v->type == JS_TOBJECT && v->u.object->type == JS_CREGEXP)
		return &v->u.object->u.r;
	js_typeerror(J, "not a regexp");
}