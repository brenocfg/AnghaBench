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
struct TYPE_3__ {scalar_t__ num_points; int* tags; int /*<<< orphan*/  valid; int /*<<< orphan*/ * points; } ;
typedef  int /*<<< orphan*/  FT_Vector ;
typedef  scalar_t__ FT_UInt ;
typedef  TYPE_1__* FT_StrokeBorder ;
typedef  int FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int FT_STROKE_TAG_BEGIN ; 
 int FT_STROKE_TAG_END ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static FT_Error
  ft_stroke_border_get_counts( FT_StrokeBorder  border,
                               FT_UInt         *anum_points,
                               FT_UInt         *anum_contours )
  {
    FT_Error  error        = FT_Err_Ok;
    FT_UInt   num_points   = 0;
    FT_UInt   num_contours = 0;

    FT_UInt     count      = border->num_points;
    FT_Vector*  point      = border->points;
    FT_Byte*    tags       = border->tags;
    FT_Int      in_contour = 0;


    for ( ; count > 0; count--, num_points++, point++, tags++ )
    {
      if ( tags[0] & FT_STROKE_TAG_BEGIN )
      {
        if ( in_contour != 0 )
          goto Fail;

        in_contour = 1;
      }
      else if ( in_contour == 0 )
        goto Fail;

      if ( tags[0] & FT_STROKE_TAG_END )
      {
        in_contour = 0;
        num_contours++;
      }
    }

    if ( in_contour != 0 )
      goto Fail;

    border->valid = TRUE;

  Exit:
    *anum_points   = num_points;
    *anum_contours = num_contours;
    return error;

  Fail:
    num_points   = 0;
    num_contours = 0;
    goto Exit;
  }