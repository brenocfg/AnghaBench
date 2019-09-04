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
typedef  int /*<<< orphan*/  some_floats ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

extern /**/

void dummy(void)
{
   double some_floats[] = {
      1.0501, -10.4e12, 5E+10,
#if 0   // not supported in C++ or C-pre-99, so don't try to compile it, but let our parser test it
      0x1.0p+24, 0xff.FP-8, 0x1p-23,
#endif
      4.
   };
   (void) sizeof(some_floats);

   printf("test %d",1); // https://github.com/nothings/stb/issues/13
}