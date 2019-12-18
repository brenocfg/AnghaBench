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
typedef  scalar_t__ FT_Pos ;

/* Variables and functions */
 scalar_t__ FT_MulDiv (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
  BBox_Conic_Check( FT_Pos   y1,
                    FT_Pos   y2,
                    FT_Pos   y3,
                    FT_Pos*  min,
                    FT_Pos*  max )
  {
    /* This function is only called when a control off-point is outside */
    /* the bbox that contains all on-points.  It finds a local extremum */
    /* within the segment, equal to (y1*y3 - y2*y2)/(y1 - 2*y2 + y3).   */
    /* Or, offsetting from y2, we get                                   */

    y1 -= y2;
    y3 -= y2;
    y2 += FT_MulDiv( y1, y3, y1 + y3 );

    if ( y2 < *min )
      *min = y2;
    if ( y2 > *max )
      *max = y2;
  }