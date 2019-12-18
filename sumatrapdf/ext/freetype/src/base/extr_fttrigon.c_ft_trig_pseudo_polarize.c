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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ FT_Vector ;
typedef  int FT_Int ;
typedef  int FT_Fixed ;
typedef  int FT_Angle ;

/* Variables and functions */
 int FT_ANGLE_PI ; 
 int FT_ANGLE_PI2 ; 
 int FT_PAD_ROUND (int,int) ; 
 int FT_TRIG_MAX_ITERS ; 
 int* ft_trig_arctan_table ; 

__attribute__((used)) static void
  ft_trig_pseudo_polarize( FT_Vector*  vec )
  {
    FT_Angle         theta;
    FT_Int           i;
    FT_Fixed         x, y, xtemp, b;
    const FT_Angle  *arctanptr;


    x = vec->x;
    y = vec->y;

    /* Get the vector into [-PI/4,PI/4] sector */
    if ( y > x )
    {
      if ( y > -x )
      {
        theta =  FT_ANGLE_PI2;
        xtemp =  y;
        y     = -x;
        x     =  xtemp;
      }
      else
      {
        theta =  y > 0 ? FT_ANGLE_PI : -FT_ANGLE_PI;
        x     = -x;
        y     = -y;
      }
    }
    else
    {
      if ( y < -x )
      {
        theta = -FT_ANGLE_PI2;
        xtemp = -y;
        y     =  x;
        x     =  xtemp;
      }
      else
      {
        theta = 0;
      }
    }

    arctanptr = ft_trig_arctan_table;

    /* Pseudorotations, with right shifts */
    for ( i = 1, b = 1; i < FT_TRIG_MAX_ITERS; b <<= 1, i++ )
    {
      if ( y > 0 )
      {
        xtemp  = x + ( ( y + b ) >> i );
        y      = y - ( ( x + b ) >> i );
        x      = xtemp;
        theta += *arctanptr++;
      }
      else
      {
        xtemp  = x - ( ( y + b ) >> i );
        y      = y + ( ( x + b ) >> i );
        x      = xtemp;
        theta -= *arctanptr++;
      }
    }

    /* round theta to acknowledge its error that mostly comes */
    /* from accumulated rounding errors in the arctan table   */
    if ( theta >= 0 )
      theta = FT_PAD_ROUND( theta, 16 );
    else
      theta = -FT_PAD_ROUND( -theta, 16 );

    vec->x = x;
    vec->y = theta;
  }