#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  gccounter; TYPE_2__* gcfun; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_19__ {int line; int script; int strict; char* name; int /*<<< orphan*/  filename; struct TYPE_19__* gcnext; scalar_t__ gcmark; } ;
typedef  TYPE_2__ js_Function ;
struct TYPE_20__ {char* string; } ;
typedef  TYPE_3__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  cfunbody (TYPE_1__*,TYPE_2__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  js_intern (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* js_malloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static js_Function *newfun(js_State *J, int line, js_Ast *name, js_Ast *params, js_Ast *body, int script, int default_strict)
{
	js_Function *F = js_malloc(J, sizeof *F);
	memset(F, 0, sizeof *F);
	F->gcmark = 0;
	F->gcnext = J->gcfun;
	J->gcfun = F;
	++J->gccounter;

	F->filename = js_intern(J, J->filename);
	F->line = line;
	F->script = script;
	F->strict = default_strict;
	F->name = name ? name->string : "";

	cfunbody(J, F, name, params, body);

	return F;
}