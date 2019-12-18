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
typedef  int /*<<< orphan*/  fz_css_selector ;
struct TYPE_4__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * declaration; int /*<<< orphan*/ * selector; } ;
typedef  TYPE_1__ fz_css_rule ;
typedef  int /*<<< orphan*/  fz_css_property ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static fz_css_rule *fz_new_css_rule(fz_context *ctx, fz_pool *pool, fz_css_selector *selector, fz_css_property *declaration)
{
	fz_css_rule *rule = fz_pool_alloc(ctx, pool, sizeof *rule);
	rule->selector = selector;
	rule->declaration = declaration;
	rule->next = NULL;
	return rule;
}