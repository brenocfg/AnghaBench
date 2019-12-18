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
 int FT_ULONG_MAX ; 
 unsigned long* a2i ; 
 int /*<<< orphan*/  ddigits ; 
 scalar_t__ sbitset (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static unsigned long
  _bdf_atoul( char*  s )
  {
    unsigned long  v;


    if ( s == 0 || *s == 0 )
      return 0;

    for ( v = 0; sbitset( ddigits, *s ); s++ )
    {
      if ( v < ( FT_ULONG_MAX - 9 ) / 10 )
        v = v * 10 + a2i[(int)*s];
      else
      {
        v = FT_ULONG_MAX;
        break;
      }
    }

    return v;
  }