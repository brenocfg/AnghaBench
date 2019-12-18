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
struct TYPE_4__ {struct TYPE_4__* psz_property; int /*<<< orphan*/  expr; struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ vlc_css_declaration_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_css_expression_Delete (int /*<<< orphan*/ ) ; 

void vlc_css_declarations_Delete( vlc_css_declaration_t *p_decl )
{
    while( p_decl )
    {
        vlc_css_declaration_t *p_next = p_decl->p_next;
        vlc_css_expression_Delete( p_decl->expr );
        free( p_decl->psz_property );
        free( p_decl );
        p_decl = p_next;
    }
}