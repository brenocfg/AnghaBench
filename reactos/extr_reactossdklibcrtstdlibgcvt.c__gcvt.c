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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,double) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

char *
_gcvt (double value, int ndigits, char *buf)
{
  char *p = buf;

  sprintf (buf, "%-#.*g", ndigits, value);

  /* It seems they expect us to return .XXXX instead of 0.XXXX  */
  if (*p == '-')
    p++;
  if (*p == '0' && p[1] == '.')
    memmove (p, p + 1, strlen (p + 1) + 1);

  /* They want Xe-YY, not X.e-YY, and XXXX instead of XXXX.  */
  p = strchr (buf, 'e');
  if (!p)
    {
      p = buf + strlen (buf);
      /* They don't want trailing zeroes.  */
      while (p[-1] == '0' && p > buf + 2)
	*--p = '\0';
    }
  if (p > buf && p[-1] == '.')
    memmove (p - 1, p, strlen (p) + 1);
  return buf;
}