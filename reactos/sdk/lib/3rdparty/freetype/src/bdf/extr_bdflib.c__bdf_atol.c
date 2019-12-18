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

/* Variables and functions */
 int FT_LONG_MAX ; 
 long* a2i ; 
 int /*<<< orphan*/  ddigits ; 
 scalar_t__ sbitset (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static long
  _bdf_atol( char*  s )
  {
    long  v, neg;


    if ( s == 0 || *s == 0 )
      return 0;

    /* Check for a minus sign. */
    neg = 0;
    if ( *s == '-' )
    {
      s++;
      neg = 1;
    }

    for ( v = 0; sbitset( ddigits, *s ); s++ )
    {
      if ( v < ( FT_LONG_MAX - 9 ) / 10 )
        v = v * 10 + a2i[(int)*s];
      else
      {
        v = FT_LONG_MAX;
        break;
      }
    }

    return ( !neg ) ? v : -v;
  }