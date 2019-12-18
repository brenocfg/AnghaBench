#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* psz_fontfile; int i_index; int b_bold; int b_italic; struct TYPE_8__* p_next; } ;
typedef  TYPE_1__ vlc_font_t ;
struct TYPE_9__ {TYPE_1__* p_fonts; } ;
typedef  TYPE_2__ vlc_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  AppendFont (TYPE_1__**,TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ unlikely (int) ; 

vlc_font_t *NewFont( char *psz_fontfile, int i_index,
                     bool b_bold, bool b_italic,
                     vlc_family_t *p_parent )
{
    vlc_font_t *p_font = calloc( 1, sizeof( *p_font ) );

    if( unlikely( !p_font ) )
    {
        free( psz_fontfile );
        return NULL;
    }

    p_font->psz_fontfile = psz_fontfile;
    p_font->i_index = i_index;
    p_font->b_bold = b_bold;
    p_font->b_italic = b_italic;

    if( p_parent )
    {
        /* Keep regular faces first */
        if( p_parent->p_fonts
         && ( p_parent->p_fonts->b_bold || p_parent->p_fonts->b_italic )
         && !b_bold && !b_italic )
        {
            p_font->p_next = p_parent->p_fonts;
            p_parent->p_fonts = p_font;
        }
        else
            AppendFont( &p_parent->p_fonts, p_font );
    }

    return p_font;
}