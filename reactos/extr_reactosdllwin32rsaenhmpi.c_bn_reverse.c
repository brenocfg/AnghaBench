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

__attribute__((used)) static void
bn_reverse (unsigned char *s, int len)
{
  int     ix, iy;
  unsigned char t;

  ix = 0;
  iy = len - 1;
  while (ix < iy) {
    t     = s[ix];
    s[ix] = s[iy];
    s[iy] = t;
    ++ix;
    --iy;
  }
}