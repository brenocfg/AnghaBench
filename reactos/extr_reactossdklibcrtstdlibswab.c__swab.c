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

void _swab (char *  src,  char *  dst,  int  sizeToCopy)

{
 if (sizeToCopy > 1)
  {
    sizeToCopy = (unsigned)sizeToCopy >> 1;

    while (sizeToCopy--) {
      char s0 = src[0];
      char s1 = src[1];
      *dst++ = s1;
      *dst++ = s0;
      src = src + 2;
    }
  }
}