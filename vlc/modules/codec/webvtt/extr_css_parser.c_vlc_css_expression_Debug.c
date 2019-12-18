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
struct TYPE_5__ {size_t i_count; TYPE_1__* seq; } ;
typedef  TYPE_2__ vlc_css_expr_t ;
struct TYPE_4__ {int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vlc_css_term_Debug (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vlc_css_expression_Debug( const vlc_css_expr_t *p_expr, int depth )
{
    if( p_expr )
    {
        for(int i=0;i<depth;i++) printf(" ");
        printf("expression: \n");
        for(size_t i=0; i<p_expr->i_count; i++)
            vlc_css_term_Debug( p_expr->seq[i].term, depth + 1 );
    }
}