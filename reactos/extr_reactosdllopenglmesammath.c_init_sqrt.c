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

__attribute__((used)) static void init_sqrt(void)
{
#ifdef FAST_MATH
   unsigned short i;
   float f;
   unsigned int *fi = (unsigned int *)&f;
                                /* to access the bits of a float in  */
                                /* C quickly we must misuse pointers */

   for(i=0; i<= 0x7f; i++) {
      *fi = 0;

      /*
       * Build a float with the bit pattern i as mantissa
       * and an exponent of 0, stored as 127
       */

      *fi = (i << 16) | (127 << 23);
      f = sqrt(f);

      /*
       * Take the square root then strip the first 7 bits of
       * the mantissa into the table
       */

      sqrttab[i] = (*fi & 0x7fffff) >> 16;

      /*
       * Repeat the process, this time with an exponent of
       * 1, stored as 128
       */

      *fi = 0;
      *fi = (i << 16) | (128 << 23);
      f = sqrt(f);
      sqrttab[i+0x80] = (*fi & 0x7fffff) >> 16;
   }
#endif /*FAST_MATH*/
}