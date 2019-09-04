#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ start; int num_points; int /*<<< orphan*/  movable; int /*<<< orphan*/ * tags; int /*<<< orphan*/ * points; } ;
typedef  int /*<<< orphan*/  FT_Vector ;
typedef  TYPE_1__* FT_StrokeBorder ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FT_ASSERT (int) ; 
 int /*<<< orphan*/  FT_STROKE_TAG_CUBIC ; 
 int /*<<< orphan*/  FT_STROKE_TAG_ON ; 
 int /*<<< orphan*/  ft_stroke_border_grow (TYPE_1__*,int) ; 

__attribute__((used)) static FT_Error
  ft_stroke_border_cubicto( FT_StrokeBorder  border,
                            FT_Vector*       control1,
                            FT_Vector*       control2,
                            FT_Vector*       to )
  {
    FT_Error  error;


    FT_ASSERT( border->start >= 0 );

    error = ft_stroke_border_grow( border, 3 );
    if ( !error )
    {
      FT_Vector*  vec = border->points + border->num_points;
      FT_Byte*    tag = border->tags   + border->num_points;


      vec[0] = *control1;
      vec[1] = *control2;
      vec[2] = *to;

      tag[0] = FT_STROKE_TAG_CUBIC;
      tag[1] = FT_STROKE_TAG_CUBIC;
      tag[2] = FT_STROKE_TAG_ON;

      border->num_points += 3;
    }

    border->movable = FALSE;

    return error;
  }