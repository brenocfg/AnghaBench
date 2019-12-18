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
typedef  int /*<<< orphan*/  vlc_css_term_t ;
typedef  int /*<<< orphan*/  vlc_css_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_css_expression_AddTerm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vlc_css_expr_t * vlc_css_expression_New( vlc_css_term_t term )
{
    vlc_css_expr_t *p_expr = calloc(1, sizeof(*p_expr));
    if(!vlc_css_expression_AddTerm( p_expr, 0, term ))
    {
        free(p_expr);
        p_expr = NULL;
    }
    return p_expr;
}