#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_13__ {char* tag; } ;
struct TYPE_12__ {char* source; int flags; } ;
struct TYPE_11__ {char* string; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {int /*<<< orphan*/  function; } ;
struct TYPE_14__ {TYPE_5__ user; int /*<<< orphan*/  number; TYPE_4__ r; TYPE_3__ s; int /*<<< orphan*/  boolean; TYPE_2__ c; TYPE_1__ f; } ;
struct TYPE_15__ {int type; TYPE_6__ u; } ;
typedef  TYPE_7__ js_Object ;
typedef  int /*<<< orphan*/  js_Buffer ;

/* Variables and functions */
#define  JS_CARRAY 141 
#define  JS_CBOOLEAN 140 
#define  JS_CCFUNCTION 139 
#define  JS_CDATE 138 
#define  JS_CERROR 137 
#define  JS_CFUNCTION 136 
#define  JS_CITERATOR 135 
#define  JS_CJSON 134 
#define  JS_CMATH 133 
#define  JS_CNUMBER 132 
#define  JS_CREGEXP 131 
#define  JS_CSCRIPT 130 
#define  JS_CSTRING 129 
#define  JS_CUSERDATA 128 
 int JS_REGEXP_G ; 
 int JS_REGEXP_I ; 
 int JS_REGEXP_M ; 
 int /*<<< orphan*/  fmtnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ js_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isnull (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 scalar_t__ js_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_7__* js_toobject (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reprarray (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  reprfun (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reprnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reprobject (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  reprstr (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void reprvalue(js_State *J, js_Buffer **sb)
{
	if (js_isundefined(J, -1))
		js_puts(J, sb, "undefined");
	else if (js_isnull(J, -1))
		js_puts(J, sb, "null");
	else if (js_isboolean(J, -1))
		js_puts(J, sb, js_toboolean(J, -1) ? "true" : "false");
	else if (js_isnumber(J, -1))
		reprnum(J, sb, js_tonumber(J, -1));
	else if (js_isstring(J, -1))
		reprstr(J, sb, js_tostring(J, -1));
	else if (js_isobject(J, -1)) {
		js_Object *obj = js_toobject(J, -1);
		switch (obj->type) {
		default:
			reprobject(J, sb);
			break;
		case JS_CARRAY:
			reprarray(J, sb);
			break;
		case JS_CFUNCTION:
		case JS_CSCRIPT:
			reprfun(J, sb, obj->u.f.function);
			break;
		case JS_CCFUNCTION:
			js_puts(J, sb, "function ");
			js_puts(J, sb, obj->u.c.name);
			js_puts(J, sb, "() { [native code] }");
			break;
		case JS_CBOOLEAN:
			js_puts(J, sb, "(new Boolean(");
			js_puts(J, sb, obj->u.boolean ? "true" : "false");
			js_puts(J, sb, "))");
			break;
		case JS_CNUMBER:
			js_puts(J, sb, "(new Number(");
			reprnum(J, sb, obj->u.number);
			js_puts(J, sb, "))");
			break;
		case JS_CSTRING:
			js_puts(J, sb, "(new String(");
			reprstr(J, sb, obj->u.s.string);
			js_puts(J, sb, "))");
			break;
		case JS_CREGEXP:
			js_putc(J, sb, '/');
			js_puts(J, sb, obj->u.r.source);
			js_putc(J, sb, '/');
			if (obj->u.r.flags & JS_REGEXP_G) js_putc(J, sb, 'g');
			if (obj->u.r.flags & JS_REGEXP_I) js_putc(J, sb, 'i');
			if (obj->u.r.flags & JS_REGEXP_M) js_putc(J, sb, 'm');
			break;
		case JS_CDATE:
			js_puts(J, sb, "(new Date(");
			fmtnum(J, sb, obj->u.number);
			js_puts(J, sb, "))");
			break;
		case JS_CERROR:
			js_puts(J, sb, "(new ");
			js_getproperty(J, -1, "name");
			js_puts(J, sb, js_tostring(J, -1));
			js_pop(J, 1);
			js_putc(J, sb, '(');
			js_getproperty(J, -1, "message");
			reprstr(J, sb, js_tostring(J, -1));
			js_pop(J, 1);
			js_puts(J, sb, "))");
			break;
		case JS_CMATH:
			js_puts(J, sb, "Math");
			break;
		case JS_CJSON:
			js_puts(J, sb, "JSON");
			break;
		case JS_CITERATOR:
			js_puts(J, sb, "[iterator ");
			break;
		case JS_CUSERDATA:
			js_puts(J, sb, "[userdata ");
			js_puts(J, sb, obj->u.user.tag);
			js_putc(J, sb, ']');
			break;
		}
	}
}