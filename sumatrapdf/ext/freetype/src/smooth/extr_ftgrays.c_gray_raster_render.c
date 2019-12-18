#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gray_TWorker ;
struct TYPE_8__ {scalar_t__ pitch; scalar_t__ origin; } ;
struct TYPE_10__ {scalar_t__ n_points; int n_contours; scalar_t__* contours; int /*<<< orphan*/  points; } ;
struct TYPE_13__ {scalar_t__ min_ex; scalar_t__ min_ey; scalar_t__ max_ex; scalar_t__ max_ey; int /*<<< orphan*/ * render_span_data; void* render_span; TYPE_1__ target; TYPE_3__ outline; } ;
struct TYPE_12__ {scalar_t__ xMin; scalar_t__ yMin; scalar_t__ xMax; scalar_t__ yMax; } ;
struct TYPE_11__ {int rows; scalar_t__ pitch; scalar_t__ width; scalar_t__ buffer; } ;
struct TYPE_9__ {int flags; TYPE_5__ clip_box; int /*<<< orphan*/ * user; scalar_t__ gray_spans; TYPE_4__* target; scalar_t__ source; } ;
typedef  void* FT_Raster_Span_Func ;
typedef  TYPE_2__ FT_Raster_Params ;
typedef  int /*<<< orphan*/  FT_Raster ;
typedef  void* FT_Pos ;
typedef  TYPE_3__ FT_Outline ;
typedef  TYPE_4__ FT_Bitmap ;
typedef  TYPE_5__ FT_BBox ;

/* Variables and functions */
 int FT_RASTER_FLAG_AA ; 
 int FT_RASTER_FLAG_CLIP ; 
 int FT_RASTER_FLAG_DIRECT ; 
 int FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_Argument ; 
 int /*<<< orphan*/  Invalid_Mode ; 
 int /*<<< orphan*/  Invalid_Outline ; 
 int /*<<< orphan*/  RAS_VAR ; 
 int gray_convert_glyph (int /*<<< orphan*/ ) ; 
 TYPE_6__ ras ; 

__attribute__((used)) static int
  gray_raster_render( FT_Raster                raster,
                      const FT_Raster_Params*  params )
  {
    const FT_Outline*  outline    = (const FT_Outline*)params->source;
    const FT_Bitmap*   target_map = params->target;
    FT_BBox            clip;

#ifndef FT_STATIC_RASTER
    gray_TWorker  worker[1];
#endif


    if ( !raster )
      return FT_THROW( Invalid_Argument );

    /* this version does not support monochrome rendering */
    if ( !( params->flags & FT_RASTER_FLAG_AA ) )
      return FT_THROW( Invalid_Mode );

    if ( !outline )
      return FT_THROW( Invalid_Outline );

    /* return immediately if the outline is empty */
    if ( outline->n_points == 0 || outline->n_contours <= 0 )
      return 0;

    if ( !outline->contours || !outline->points )
      return FT_THROW( Invalid_Outline );

    if ( outline->n_points !=
           outline->contours[outline->n_contours - 1] + 1 )
      return FT_THROW( Invalid_Outline );

    ras.outline = *outline;

    if ( params->flags & FT_RASTER_FLAG_DIRECT )
    {
      if ( !params->gray_spans )
        return 0;

      ras.render_span      = (FT_Raster_Span_Func)params->gray_spans;
      ras.render_span_data = params->user;
    }
    else
    {
      /* if direct mode is not set, we must have a target bitmap */
      if ( !target_map )
        return FT_THROW( Invalid_Argument );

      /* nothing to do */
      if ( !target_map->width || !target_map->rows )
        return 0;

      if ( !target_map->buffer )
        return FT_THROW( Invalid_Argument );

      if ( target_map->pitch < 0 )
        ras.target.origin = target_map->buffer;
      else
        ras.target.origin = target_map->buffer
              + ( target_map->rows - 1 ) * (unsigned int)target_map->pitch;

      ras.target.pitch = target_map->pitch;

      ras.render_span      = (FT_Raster_Span_Func)NULL;
      ras.render_span_data = NULL;
    }

    /* compute clipping box */
    if ( params->flags & FT_RASTER_FLAG_DIRECT &&
         params->flags & FT_RASTER_FLAG_CLIP   )
      clip = params->clip_box;
    else
    {
      /* compute clip box from target pixmap */
      clip.xMin = 0;
      clip.yMin = 0;
      clip.xMax = (FT_Pos)target_map->width;
      clip.yMax = (FT_Pos)target_map->rows;
    }

    /* clip to target bitmap, exit if nothing to do */
    ras.min_ex = clip.xMin;
    ras.min_ey = clip.yMin;
    ras.max_ex = clip.xMax;
    ras.max_ey = clip.yMax;

    if ( ras.max_ex <= ras.min_ex || ras.max_ey <= ras.min_ey )
      return 0;

    return gray_convert_glyph( RAS_VAR );
  }