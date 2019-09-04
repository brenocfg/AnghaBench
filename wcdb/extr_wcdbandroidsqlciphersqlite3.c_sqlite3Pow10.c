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
typedef  double LONGDOUBLE_TYPE ;

/* Variables and functions */

__attribute__((used)) static LONGDOUBLE_TYPE sqlite3Pow10(int E){
#if defined(_MSC_VER)
  static const LONGDOUBLE_TYPE x[] = {
    1.0e+001,
    1.0e+002,
    1.0e+004,
    1.0e+008,
    1.0e+016,
    1.0e+032,
    1.0e+064,
    1.0e+128,
    1.0e+256
  };
  LONGDOUBLE_TYPE r = 1.0;
  int i;
  assert( E>=0 && E<=307 );
  for(i=0; E!=0; i++, E >>=1){
    if( E & 1 ) r *= x[i];
  }
  return r;
#else
  LONGDOUBLE_TYPE x = 10.0;
  LONGDOUBLE_TYPE r = 1.0;
  while(1){
    if( E & 1 ) r *= x;
    E >>= 1;
    if( E==0 ) break;
    x *= x;
  }
  return r; 
#endif
}