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
typedef  int /*<<< orphan*/  FT_UInt32 ;
typedef  int FT_Pos ;
typedef  int FT_Int ;

/* Variables and functions */
 int FT_ABS (int) ; 
 int FT_MSB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Pos
  cubic_peak( FT_Pos  q1,
              FT_Pos  q2,
              FT_Pos  q3,
              FT_Pos  q4 )
  {
    FT_Pos  peak = 0;
    FT_Int  shift;


    /* This function finds a peak of a cubic segment if it is above 0    */
    /* using iterative bisection of the segment, or returns 0.           */
    /* The fixed-point arithmetic of bisection is inherently stable      */
    /* but may loose accuracy in the two lowest bits.  To compensate,    */
    /* we upscale the segment if there is room.  Large values may need   */
    /* to be downscaled to avoid overflows during bisection.             */
    /* It is called with either q2 or q3 positive, which is necessary    */
    /* for the peak to exist and avoids undefined FT_MSB.                */

    shift = 27 - FT_MSB( (FT_UInt32)( FT_ABS( q1 ) |
                                      FT_ABS( q2 ) |
                                      FT_ABS( q3 ) |
                                      FT_ABS( q4 ) ) );

    if ( shift > 0 )
    {
      /* upscaling too much just wastes time */
      if ( shift > 2 )
        shift = 2;

      q1 <<=  shift;
      q2 <<=  shift;
      q3 <<=  shift;
      q4 <<=  shift;
    }
    else
    {
      q1 >>= -shift;
      q2 >>= -shift;
      q3 >>= -shift;
      q4 >>= -shift;
    }

    /* for a peak to exist above 0, the cubic segment must have */
    /* at least one of its control off-points above 0.          */
    while ( q2 > 0 || q3 > 0 )
    {
      /* determine which half contains the maximum and split */
      if ( q1 + q2 > q3 + q4 ) /* first half */
      {
        q4 = q4 + q3;
        q3 = q3 + q2;
        q2 = q2 + q1;
        q4 = q4 + q3;
        q3 = q3 + q2;
        q4 = ( q4 + q3 ) / 8;
        q3 = q3 / 4;
        q2 = q2 / 2;
      }
      else                     /* second half */
      {
        q1 = q1 + q2;
        q2 = q2 + q3;
        q3 = q3 + q4;
        q1 = q1 + q2;
        q2 = q2 + q3;
        q1 = ( q1 + q2 ) / 8;
        q2 = q2 / 4;
        q3 = q3 / 2;
      }

      /* check whether either end reached the maximum */
      if ( q1 == q2 && q1 >= q3 )
      {
        peak = q1;
        break;
      }
      if ( q3 == q4 && q2 <= q4 )
      {
        peak = q4;
        break;
      }
    }

    if ( shift > 0 )
      peak >>=  shift;
    else
      peak <<= -shift;

    return peak;
  }