#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* lcd_geometry; } ;
struct TYPE_8__ {TYPE_7__* library; } ;
struct TYPE_12__ {int /*<<< orphan*/  raster; TYPE_3__* clazz; TYPE_1__ root; } ;
struct TYPE_11__ {int x; scalar_t__ y; } ;
struct TYPE_10__ {TYPE_2__* raster_class; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* raster_reset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ FT_Vector ;
typedef  TYPE_5__* FT_Renderer ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_LCD_FILTER_DEFAULT ; 
 int /*<<< orphan*/  FT_Library_SetLcdFilter (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ft_smooth_init( FT_Renderer  render )
  {

#ifndef FT_CONFIG_OPTION_SUBPIXEL_RENDERING

    FT_Vector*  sub = render->root.library->lcd_geometry;


    /* set up default subpixel geometry for striped RGB panels. */
    sub[0].x = -21;
    sub[0].y = 0;
    sub[1].x = 0;
    sub[1].y = 0;
    sub[2].x = 21;
    sub[2].y = 0;

#elif 0   /* or else, once ClearType patents expire */

    FT_Library_SetLcdFilter( render->root.library, FT_LCD_FILTER_DEFAULT );

#endif

    render->clazz->raster_class->raster_reset( render->raster, NULL, 0 );

    return 0;
  }