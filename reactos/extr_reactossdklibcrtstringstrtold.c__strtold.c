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
 scalar_t__ isspace (char const) ; 
 double* powten ; 

long double
_strtold(const char *s, char **sret)
{
  double r;		/* result */
  int e, ne;			/* exponent */
  int sign;			/* +- 1.0 */
  int esign;
  int flags=0;
  int l2powm1;

  r = 0.0L;
  sign = 1;
  e = ne = 0;
  esign = 1;

  while(*s && isspace(*s))
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
    r *= 10.0L;
    r += *s - '0';
    s++;
  }

  if (*s == '.')
  {
    s++;
    while ((*s >= '0') && (*s <= '9'))
    {
      flags |= 2;
      r *= 10.0L;
      r += *s - '0';
      s++;
      ne++;
    }
  }
  if (flags == 0)
  {
    if (sret)
      *sret = (char *)s;
    return 0.0L;
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
    while ((*s >= '0') && (*s <= '9'))
    {
      e *= 10;
      e += *s - '0';
      s++;
    }
  }
  if (esign < 0)
  {
    esign = -esign;
    e = -e;
  }
  e = e - ne;
  if (e < -4096)
  {
    /* possibly subnormal number, 10^e would overflow */
    r *= 1.0e-2048L;
    e += 2048;
  }
  if (e < 0)
  {
    e = -e;
    esign = -esign;
  }
  if (e >= 8192)
    e = 8191;
  if (e)
  {
    double d = 1.0L;
    l2powm1 = 0;
    while (e)
    {
      if (e & 1)
	d *= powten[l2powm1];
      e >>= 1;
      l2powm1++;
    }
    if (esign > 0)
      r *= d;
    else
      r /= d;
  }
  if (sret)
    *sret = (char *)s;
  return r * sign;

  return 0;
}