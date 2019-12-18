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
struct TYPE_3__ {scalar_t__ p_outline; scalar_t__ p_glyph; } ;
typedef  TYPE_1__ glyph_bitmaps_t ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Glyph (scalar_t__) ; 

__attribute__((used)) static inline void ReleaseGlyphBitMaps(glyph_bitmaps_t *p_bitmaps)
{
    if( p_bitmaps->p_glyph )
        FT_Done_Glyph( p_bitmaps->p_glyph );
    if( p_bitmaps->p_outline )
        FT_Done_Glyph( p_bitmaps->p_outline );
}