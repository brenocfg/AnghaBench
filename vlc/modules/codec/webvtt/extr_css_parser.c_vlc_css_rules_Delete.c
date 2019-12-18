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
struct TYPE_4__ {int /*<<< orphan*/  p_declarations; int /*<<< orphan*/  p_selectors; struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ vlc_css_rule_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_css_declarations_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_css_selectors_Delete (int /*<<< orphan*/ ) ; 

void vlc_css_rules_Delete( vlc_css_rule_t *p_rule )
{
    while(p_rule)
    {
        vlc_css_rule_t *p_next = p_rule->p_next;
        vlc_css_selectors_Delete( p_rule->p_selectors );
        vlc_css_declarations_Delete( p_rule->p_declarations );
        free(p_rule);
        p_rule = p_next;
    }
}