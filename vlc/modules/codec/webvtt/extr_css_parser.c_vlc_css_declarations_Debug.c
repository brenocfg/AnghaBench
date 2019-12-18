#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* psz_property; struct TYPE_3__* p_next; int /*<<< orphan*/  expr; } ;
typedef  TYPE_1__ vlc_css_declaration_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vlc_css_expression_Debug (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vlc_css_declarations_Debug( const vlc_css_declaration_t *p_decl, int depth )
{
    while( p_decl )
    {
        for(int i=0;i<depth;i++) printf(" ");
        printf("declaration: %s\n", p_decl->psz_property );
        vlc_css_expression_Debug( p_decl->expr, depth + 1 );
        p_decl = p_decl->p_next;
    }
}