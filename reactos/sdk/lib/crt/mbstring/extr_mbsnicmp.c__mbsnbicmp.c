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
 int _mbbtoupper (unsigned char const) ; 
 int /*<<< orphan*/  _mbclen2 (unsigned char const) ; 

int _mbsnbicmp(const unsigned char *s1, const unsigned char *s2, size_t n)
{
  if (n == 0)
    return 0;
  do {
    if (_mbbtoupper(*s1) != _mbbtoupper(*s2))
      return _mbbtoupper(*(unsigned const char *)s1) - _mbbtoupper(*(unsigned const char *)s2);
    s1 += _mbclen2(*s1);
    s2 += _mbclen2(*s2);

    if (*s1 == 0)
      break;
    n--;
  } while (n > 0);
  return 0;
}