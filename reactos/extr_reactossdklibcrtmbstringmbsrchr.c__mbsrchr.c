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
 unsigned int _mbsnextc (unsigned char const*) ; 

unsigned char * _mbsrchr(const unsigned char *src, unsigned int val)
{
  unsigned int c;
  unsigned char *match = NULL;

  if (!src)
    return NULL;

  while (1)
  {
    c = _mbsnextc(src);
    if (c == val)
      match = (unsigned char*)src;
    if (!c)
      return match;
    src += (c > 255) ? 2 : 1;
  }
}