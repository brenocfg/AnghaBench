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
typedef  double FT_Fixed ;

/* Variables and functions */
 int FT_ANGLE_2PI ; 
 int FT_Atan2 (double,double) ; 
 int SPI ; 
 int abs (int) ; 
 double cos (double) ; 
 int /*<<< orphan*/  printf (char*,double,double,int,int) ; 
 double sin (double) ; 

__attribute__((used)) static void
  test_atan2( void )
  {
    int  i;


    for ( i = 0; i < FT_ANGLE_2PI; i += 0x10000L )
    {
      FT_Fixed  c2, s2;
      double    l, a, c1, s1;
      int       j;


      l  = 5.0;
      a  = i*SPI;

      c1 = l * cos(a);
      s1 = l * sin(a);

      c2 = (FT_Fixed)(c1*65536.0);
      s2 = (FT_Fixed)(s1*65536.0);

      j  = FT_Atan2( c2, s2 );
      if ( j < 0 )
        j += FT_ANGLE_2PI;

      if ( abs( i - j ) > 1 )
      {
        printf( "FT_Atan2( %.7f, %.7f ) = %.5f, atan = %.5f\n",
                c2/65536.0, s2/65536.0, j/65536.0, i/65536.0 );
      }
    }
  }