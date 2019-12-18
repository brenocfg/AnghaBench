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
struct TYPE_5__ {int i_character_count; struct TYPE_5__* p_character; scalar_t__ p_shadow; scalar_t__ p_outline; scalar_t__ p_glyph; } ;
typedef  TYPE_1__ line_desc_t ;
typedef  TYPE_1__ line_character_t ;
typedef  int /*<<< orphan*/  FT_Glyph ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Glyph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void FreeLine( line_desc_t *p_line )
{
    for( int i = 0; i < p_line->i_character_count; i++ )
    {
        line_character_t *ch = &p_line->p_character[i];
        FT_Done_Glyph( (FT_Glyph)ch->p_glyph );
        if( ch->p_outline )
            FT_Done_Glyph( (FT_Glyph)ch->p_outline );
        if( ch->p_shadow )
            FT_Done_Glyph( (FT_Glyph)ch->p_shadow );
    }

//    if( p_line->p_ruby )
//        FreeLine( p_line->p_ruby );

    free( p_line->p_character );
    free( p_line );
}