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
typedef  int /*<<< orphan*/  real ;

/* Variables and functions */
 int TOINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dct64_1_486 (int*,int*,int*,int*) ; 

void dct64_i486(int *a,int *b,real *samples)
{
  int bufs[64];
  int i;

#ifdef REAL_IS_FIXED  
#define TOINT(a) ((a) * 32768 / (int)REAL_FACTOR)

  for(i=0;i<32;i++) {
    bufs[i]=TOINT(samples[i]);
  }
#else      
  int *p = bufs;
  register double const scale = ((65536.0 * 32) + 1) * 65536.0;
  
  for(i=0;i<32;i++) {
    *((double *) (p++)) = scale + *samples++; /* beware on bufs overrun: 8B store from x87 */
  }
#endif
  
  dct64_1_486(a,b,bufs+32,bufs);
}