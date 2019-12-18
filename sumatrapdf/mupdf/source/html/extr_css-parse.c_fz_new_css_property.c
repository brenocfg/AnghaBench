#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_pool ;
typedef  int /*<<< orphan*/  fz_css_value ;
struct TYPE_4__ {int spec; int /*<<< orphan*/ * next; scalar_t__ important; int /*<<< orphan*/ * value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ fz_css_property ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_pool_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static fz_css_property *fz_new_css_property(fz_context *ctx, fz_pool *pool, const char *name, fz_css_value *value, int spec)
{
	fz_css_property *prop = fz_pool_alloc(ctx, pool, sizeof *prop);
	prop->name = fz_pool_strdup(ctx, pool, name);
	prop->value = value;
	prop->spec = spec;
	prop->important = 0;
	prop->next = NULL;
	return prop;
}