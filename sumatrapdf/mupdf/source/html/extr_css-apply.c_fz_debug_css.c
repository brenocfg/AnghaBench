#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ fz_css_rule ;
struct TYPE_6__ {TYPE_1__* rule; } ;
typedef  TYPE_2__ fz_css ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  print_rule (TYPE_1__*) ; 

void
fz_debug_css(fz_context *ctx, fz_css *css)
{
	fz_css_rule *rule = css->rule;
	while (rule)
	{
		print_rule(rule);
		rule = rule->next;
	}
}