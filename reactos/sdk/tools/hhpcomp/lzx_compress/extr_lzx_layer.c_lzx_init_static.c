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
 int* extra_bits ; 
 double log (int) ; 
 int* position_base ; 
 double rloge2 ; 

__attribute__((used)) static void lzx_init_static(void)
{
  int i, j;

  if (extra_bits[49]) return;

  rloge2 = 1.0/log(2);
  for (i=0, j=0; i <= 50; i += 2) {
    extra_bits[i] = extra_bits[i+1] = j; /* 0,0,0,0,1,1,2,2,3,3... */
    if ((i != 0) && (j < 17)) j++; /* 0,0,1,2,3,4...15,16,17,17,17,17... */
  }

  for (i=0, j=0; i <= 50; i++) {
    position_base[i] = j; /* 0,1,2,3,4,6,8,12,16,24,32,... */
    j += 1 << extra_bits[i]; /* 1,1,1,1,2,2,4,4,8,8,16,16,32,32,... */
  }
}