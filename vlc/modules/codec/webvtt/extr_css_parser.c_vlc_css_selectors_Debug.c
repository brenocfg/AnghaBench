#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_first; } ;
struct TYPE_5__ {int combinator; struct TYPE_5__* p_next; TYPE_1__ specifiers; struct TYPE_5__* p_matchsel; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_2__ vlc_css_selector_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void vlc_css_selectors_Debug( const vlc_css_selector_t *p_sel, int depth )
{
    while( p_sel )
    {
        for(int i=0;i<depth;i++) printf(" "); printf("selector %c%s:\n", p_sel->combinator, p_sel->psz_name );
        vlc_css_selectors_Debug( p_sel->p_matchsel, depth + 1 );
        vlc_css_selectors_Debug( p_sel->specifiers.p_first, depth + 1 );
        p_sel = p_sel->p_next;
    }
}