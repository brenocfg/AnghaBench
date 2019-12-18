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
 scalar_t__ cubic_peak (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
  BBox_Cubic_Check( FT_Pos   p1,
                    FT_Pos   p2,
                    FT_Pos   p3,
                    FT_Pos   p4,
                    FT_Pos*  min,
                    FT_Pos*  max )
  {
    /* This function is only called when a control off-point is outside  */
    /* the bbox that contains all on-points.  So at least one of the     */
    /* conditions below holds and cubic_peak is called with at least one */
    /* non-zero argument.                                                */

    if ( p2 > *max || p3 > *max )
      *max += cubic_peak( p1 - *max, p2 - *max, p3 - *max, p4 - *max );

    /* now flip the signs to update the minimum */
    if ( p2 < *min || p3 < *min )
      *min -= cubic_peak( *min - p1, *min - p2, *min - p3, *min - p4 );
  }