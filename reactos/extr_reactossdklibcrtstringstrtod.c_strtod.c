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

double
strtod(const char *s, char **sret)
{
  long double r;		/* result */
  int e;			/* exponent */
  long double d;		/* scale */
  int sign;			/* +- 1.0 */
  int esign;
  int i;
  int flags=0;

  r = 0.0;
  sign = 1;
  e = 0;
  esign = 1;

  if (s == NULL)
     return r;


  while ((*s == ' ') || (*s == '\t'))
    s++;

  if (*s == '+')
    s++;
  else if (*s == '-')
  {
    sign = -1;
    s++;
  }

  while ((*s >= '0') && (*s <= '9'))
  {
    flags |= 1;
    r *= 10.0;
    r += *s - '0';
    s++;
  }

  if (*s == '.')
  {
    d = 0.1L;
    s++;
    while ((*s >= '0') && (*s <= '9'))
    {
      flags |= 2;
      r += d * (*s - '0');
      s++;
      d *= 0.1L;
    }
  }

  if (flags == 0)
  {
    if (sret)
      *sret = (char *)s;
    return 0;
  }

  if ((*s == 'e') || (*s == 'E'))
  {
    s++;
    if (*s == '+')
      s++;
    else if (*s == '-')
    {
      s++;
      esign = -1;
    }
    if ((*s < '0') || (*s > '9'))
    {
      if (sret)
	*sret = (char *)s;
      return r;
    }

    while ((*s >= '0') && (*s <= '9'))
    {
      e *= 10;
      e += *s - '0';
      s++;
    }
  }

  if (esign < 0)
    for (i = 1; i <= e; i++)
      r *= 0.1L;
  else
    for (i = 1; i <= e; i++)
      r *= 10.0;

  if (sret)
    *sret = (char *)s;
  return r * sign;
}