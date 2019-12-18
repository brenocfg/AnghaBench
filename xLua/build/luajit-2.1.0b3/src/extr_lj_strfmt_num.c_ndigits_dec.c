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
typedef  int uint32_t ;
typedef  size_t MSize ;

/* Variables and functions */
 int lj_fls (int) ; 
 int* ndigits_dec_threshold ; 

__attribute__((used)) static MSize ndigits_dec(uint32_t x)
{
  MSize t = ((lj_fls(x | 1) * 77) >> 8) + 1; /* 2^8/77 is roughly log2(10) */
  return t + (x > ndigits_dec_threshold[t]);
}