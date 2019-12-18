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
struct TYPE_4__ {size_t i_count; struct TYPE_4__* seq; int /*<<< orphan*/  term; } ;
typedef  TYPE_1__ vlc_css_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_css_term_Clean (int /*<<< orphan*/ ) ; 

void vlc_css_expression_Delete( vlc_css_expr_t *p_expr )
{
    if( p_expr )
    {
        for(size_t i=0; i<p_expr->i_count; i++)
            vlc_css_term_Clean( p_expr->seq[i].term );
        free( p_expr->seq );
    }
    free( p_expr );
}