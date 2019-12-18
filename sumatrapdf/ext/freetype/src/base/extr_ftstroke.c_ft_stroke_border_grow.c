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
struct TYPE_3__ {scalar_t__ max_points; scalar_t__ num_points; int /*<<< orphan*/  tags; int /*<<< orphan*/  points; int /*<<< orphan*/  memory; } ;
typedef  scalar_t__ FT_UInt ;
typedef  TYPE_1__* FT_StrokeBorder ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ FT_RENEW_ARRAY (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static FT_Error
  ft_stroke_border_grow( FT_StrokeBorder  border,
                         FT_UInt          new_points )
  {
    FT_UInt   old_max = border->max_points;
    FT_UInt   new_max = border->num_points + new_points;
    FT_Error  error   = FT_Err_Ok;


    if ( new_max > old_max )
    {
      FT_UInt    cur_max = old_max;
      FT_Memory  memory  = border->memory;


      while ( cur_max < new_max )
        cur_max += ( cur_max >> 1 ) + 16;

      if ( FT_RENEW_ARRAY( border->points, old_max, cur_max ) ||
           FT_RENEW_ARRAY( border->tags,   old_max, cur_max ) )
        goto Exit;

      border->max_points = cur_max;
    }

  Exit:
    return error;
  }