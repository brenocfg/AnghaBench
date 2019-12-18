#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ xMin; scalar_t__ xMax; scalar_t__ yMin; scalar_t__ yMax; } ;
struct TYPE_7__ {scalar_t__ left; scalar_t__ top; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ FT_Vector ;
typedef  scalar_t__ FT_Pos ;
typedef  int /*<<< orphan*/  FT_Glyph ;
typedef  TYPE_2__* FT_BitmapGlyph ;
typedef  TYPE_3__ FT_BBox ;

/* Variables and functions */
 void* FT_CEIL (scalar_t__) ; 

__attribute__((used)) static void FixGlyph( FT_Glyph glyph, FT_BBox *p_bbox,
                      FT_Pos i_x_advance, FT_Pos i_y_advance,
                      const FT_Vector *p_pen )
{
    FT_BitmapGlyph glyph_bmp = (FT_BitmapGlyph)glyph;
    if( p_bbox->xMin >= p_bbox->xMax )
    {
        p_bbox->xMin = FT_CEIL(p_pen->x);
        p_bbox->xMax = FT_CEIL(p_pen->x + i_x_advance);
        glyph_bmp->left = p_bbox->xMin;
    }
    if( p_bbox->yMin >= p_bbox->yMax )
    {
        p_bbox->yMax = FT_CEIL(p_pen->y);
        p_bbox->yMin = FT_CEIL(p_pen->y + i_y_advance);
        glyph_bmp->top  = p_bbox->yMax;
    }
}