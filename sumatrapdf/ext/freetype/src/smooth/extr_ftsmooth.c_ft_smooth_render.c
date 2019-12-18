#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FT_Vector ;
typedef  int /*<<< orphan*/  FT_Renderer ;
typedef  scalar_t__ FT_Render_Mode ;
typedef  int /*<<< orphan*/  FT_GlyphSlot ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 scalar_t__ FT_RENDER_MODE_LIGHT ; 
 scalar_t__ FT_RENDER_MODE_NORMAL ; 
 int /*<<< orphan*/  ft_smooth_render_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static FT_Error
  ft_smooth_render( FT_Renderer       render,
                    FT_GlyphSlot      slot,
                    FT_Render_Mode    mode,
                    const FT_Vector*  origin )
  {
    if ( mode == FT_RENDER_MODE_LIGHT )
      mode = FT_RENDER_MODE_NORMAL;

    return ft_smooth_render_generic( render, slot, mode, origin,
                                     FT_RENDER_MODE_NORMAL );
  }