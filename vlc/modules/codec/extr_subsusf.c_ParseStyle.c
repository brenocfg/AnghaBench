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
struct TYPE_5__ {int /*<<< orphan*/  psz_stylename; } ;
typedef  TYPE_1__ ssa_style_t ;
struct TYPE_6__ {int i_ssa_styles; TYPE_1__** pp_ssa_styles; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 char* GrabAttributeValue (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssa_style_t *ParseStyle( decoder_sys_t *p_sys, char *psz_subtitle )
{
    ssa_style_t *p_ssa_style = NULL;
    char        *psz_style = GrabAttributeValue( "style", psz_subtitle );

    if( psz_style )
    {
        for( int i = 0; i < p_sys->i_ssa_styles; i++ )
        {
            if( !strcmp( p_sys->pp_ssa_styles[i]->psz_stylename, psz_style ) )
                p_ssa_style = p_sys->pp_ssa_styles[i];
        }
        free( psz_style );
    }
    return p_ssa_style;
}