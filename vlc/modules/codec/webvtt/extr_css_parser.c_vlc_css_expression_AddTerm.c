#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_css_term_t ;
struct TYPE_4__ {int i_count; int i_alloc; TYPE_3__* seq; } ;
typedef  TYPE_1__ vlc_css_expr_t ;
struct TYPE_5__ {char op; int /*<<< orphan*/  term; } ;

/* Variables and functions */
 void* realloc (TYPE_3__*,size_t) ; 

bool vlc_css_expression_AddTerm( vlc_css_expr_t *p_expr,
                                        char op, vlc_css_term_t a )
{
    if( p_expr->i_count >= p_expr->i_alloc )
    {
        size_t i_realloc = (p_expr->i_alloc == 0) ? 1 : p_expr->i_alloc + 4;
        void *reac = realloc( p_expr->seq, i_realloc * sizeof(p_expr->seq[0]) );
        if( reac )
        {
            p_expr->seq = reac;
            p_expr->i_alloc = i_realloc;
        }
    }

    if( p_expr->i_count >= p_expr->i_alloc )
        return false;

    p_expr->seq[p_expr->i_count].op = op;
    p_expr->seq[p_expr->i_count++].term = a;
    return true;
}