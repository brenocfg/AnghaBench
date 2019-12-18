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
typedef  int /*<<< orphan*/  vlc_css_rule_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

vlc_css_rule_t * vlc_css_rule_New( void )
{
    vlc_css_rule_t *p_rule = calloc(1, sizeof(*p_rule));
    return p_rule;
}