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
 scalar_t__ isleadbyte (unsigned char const) ; 

unsigned char * _mbspbrk(const unsigned char *s1, const unsigned char *s2)
{
  const unsigned char* p;

  while (*s1)
  {
    for (p = s2; *p; p += (isleadbyte(*p) ? 2 : 1))
    {
      if (*p == *s1)
        if (!isleadbyte(*p) || (*(p+1) == *(s1 + 1)))
          return (unsigned char*)s1;
    }
    s1 += (isleadbyte(*s1) ? 2 : 1);
  }
  return NULL;
}