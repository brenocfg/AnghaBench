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
struct TYPE_4__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/ * cond; scalar_t__ combine; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ fz_css_selector ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fz_pool_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static fz_css_selector *fz_new_css_selector(fz_context *ctx, fz_pool *pool, const char *name)
{
	fz_css_selector *sel = fz_pool_alloc(ctx, pool, sizeof *sel);
	sel->name = name ? fz_pool_strdup(ctx, pool, name) : NULL;
	sel->combine = 0;
	sel->cond = NULL;
	sel->left = NULL;
	sel->right = NULL;
	sel->next = NULL;
	return sel;
}