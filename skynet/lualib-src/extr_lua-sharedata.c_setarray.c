#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct table {int /*<<< orphan*/ * array; int /*<<< orphan*/ * arraytype; } ;
struct node {int /*<<< orphan*/  v; int /*<<< orphan*/  valuetype; } ;
struct context {struct table* tbl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  setvalue (struct context*,int /*<<< orphan*/ *,int,struct node*) ; 

__attribute__((used)) static void
setarray(struct context *ctx, lua_State *L, int index, int key) {
	struct node n;
	setvalue(ctx, L, index, &n);
	struct table *tbl = ctx->tbl;
	--key;	// base 0
	tbl->arraytype[key] = n.valuetype;
	tbl->array[key] = n.v;
}