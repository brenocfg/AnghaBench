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
struct TYPE_6__ {scalar_t__ format; int /*<<< orphan*/  outline; } ;
struct TYPE_5__ {scalar_t__ glyph_format; } ;
typedef  TYPE_1__* FT_Renderer ;
typedef  TYPE_2__* FT_GlyphSlot ;
typedef  int /*<<< orphan*/  FT_BBox ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Outline_Get_CBox (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_ZERO (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
  ft_smooth_get_cbox( FT_Renderer   render,
                      FT_GlyphSlot  slot,
                      FT_BBox*      cbox )
  {
    FT_ZERO( cbox );

    if ( slot->format == render->glyph_format )
      FT_Outline_Get_CBox( &slot->outline, cbox );
  }