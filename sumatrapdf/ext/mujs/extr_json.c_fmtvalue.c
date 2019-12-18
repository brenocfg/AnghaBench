#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct TYPE_7__ {int /*<<< orphan*/  boolean; TYPE_1__ s; int /*<<< orphan*/  number; } ;
struct TYPE_8__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ js_Object ;
typedef  int /*<<< orphan*/  js_Buffer ;

/* Variables and functions */
#define  JS_CARRAY 131 
#define  JS_CBOOLEAN 130 
#define  JS_CNUMBER 129 
#define  JS_CSTRING 128 
 int /*<<< orphan*/  fmtarray (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int) ; 
 int /*<<< orphan*/  fmtnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtobject (int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_3__*,char const*,int) ; 
 int /*<<< orphan*/  fmtstr (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ js_hasproperty (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ js_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_iscallable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isnull (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  js_rot2pop1 (int /*<<< orphan*/ *) ; 
 scalar_t__ js_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fmtvalue(js_State *J, js_Buffer **sb, const char *key, const char *gap, int level)
{
	/* replacer is in 2 */
	/* holder is in -1 */

	js_getproperty(J, -1, key);

	if (js_isobject(J, -1)) {
		if (js_hasproperty(J, -1, "toJSON")) {
			if (js_iscallable(J, -1)) {
				js_copy(J, -2);
				js_pushstring(J, key);
				js_call(J, 1);
				js_rot2pop1(J);
			} else {
				js_pop(J, 1);
			}
		}
	}

	if (js_iscallable(J, 2)) {
		js_copy(J, 2); /* replacer function */
		js_copy(J, -3); /* holder as this */
		js_pushstring(J, key); /* name */
		js_copy(J, -4); /* old value */
		js_call(J, 2);
		js_rot2pop1(J); /* pop old value, leave new value on stack */
	}

	if (js_isobject(J, -1) && !js_iscallable(J, -1)) {
		js_Object *obj = js_toobject(J, -1);
		switch (obj->type) {
		case JS_CNUMBER: fmtnum(J, sb, obj->u.number); break;
		case JS_CSTRING: fmtstr(J, sb, obj->u.s.string); break;
		case JS_CBOOLEAN: js_puts(J, sb, obj->u.boolean ? "true" : "false"); break;
		case JS_CARRAY: fmtarray(J, sb, gap, level); break;
		default: fmtobject(J, sb, obj, gap, level); break;
		}
	}
	else if (js_isboolean(J, -1))
		js_puts(J, sb, js_toboolean(J, -1) ? "true" : "false");
	else if (js_isnumber(J, -1))
		fmtnum(J, sb, js_tonumber(J, -1));
	else if (js_isstring(J, -1))
		fmtstr(J, sb, js_tostring(J, -1));
	else if (js_isnull(J, -1))
		js_puts(J, sb, "null");
	else {
		js_pop(J, 1);
		return 0;
	}

	js_pop(J, 1);
	return 1;
}