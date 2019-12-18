#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_12__ {char* name; } ;
struct TYPE_11__ {TYPE_5__* function; } ;
struct TYPE_13__ {TYPE_2__ c; TYPE_1__ f; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_4__ js_Object ;
struct TYPE_15__ {char* name; int numparams; char** vartab; } ;
typedef  TYPE_5__ js_Function ;
struct TYPE_16__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_6__ js_Buffer ;

/* Variables and functions */
 scalar_t__ JS_CCFUNCTION ; 
 scalar_t__ JS_CFUNCTION ; 
 scalar_t__ JS_CSCRIPT ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_6__**,char) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,TYPE_6__**,char*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 TYPE_4__* js_toobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Fp_toString(js_State *J)
{
	js_Object *self = js_toobject(J, 0);
	js_Buffer *sb = NULL;
	int i;

	if (!js_iscallable(J, 0))
		js_typeerror(J, "not a function");

	if (self->type == JS_CFUNCTION || self->type == JS_CSCRIPT) {
		js_Function *F = self->u.f.function;

		if (js_try(J)) {
			js_free(J, sb);
			js_throw(J);
		}

		js_puts(J, &sb, "function ");
		js_puts(J, &sb, F->name);
		js_putc(J, &sb, '(');
		for (i = 0; i < F->numparams; ++i) {
			if (i > 0) js_putc(J, &sb, ',');
			js_puts(J, &sb, F->vartab[i]);
		}
		js_puts(J, &sb, ") { [byte code] }");
		js_putc(J, &sb, 0);

		js_pushstring(J, sb->s);
		js_endtry(J);
		js_free(J, sb);
	} else if (self->type == JS_CCFUNCTION) {
		if (js_try(J)) {
			js_free(J, sb);
			js_throw(J);
		}

		js_puts(J, &sb, "function ");
		js_puts(J, &sb, self->u.c.name);
		js_puts(J, &sb, "() { [native code] }");
		js_putc(J, &sb, 0);

		js_pushstring(J, sb->s);
		js_endtry(J);
		js_free(J, sb);
	} else {
		js_pushliteral(J, "function () { }");
	}
}