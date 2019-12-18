#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* psz_name; struct TYPE_5__* psz_fontfile; struct TYPE_5__* p_next; struct TYPE_5__* p_fonts; } ;
typedef  TYPE_1__ vlc_font_t ;
typedef  TYPE_1__ vlc_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void FreeFamiliesAndFonts( vlc_family_t *p_family )
{
    if( p_family->p_next )
        FreeFamiliesAndFonts( p_family->p_next );

    for( vlc_font_t *p_font = p_family->p_fonts; p_font; )
    {
        vlc_font_t *p_temp = p_font->p_next;
        free( p_font->psz_fontfile );
        free( p_font );
        p_font = p_temp;
    }

    free( p_family->psz_name );
    free( p_family );
}