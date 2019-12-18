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
typedef  char wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 int* _errno () ; 
 char towlower (char) ; 

int _wcslwr_s(wchar_t* str, size_t n)
{
  wchar_t *ptr=str;
  if (!str || !n)
  {
    if (str) *str = '\0';
    *_errno() = EINVAL;
    return EINVAL;
  }

  while (n--)
  {
    if (!*ptr) return 0;
    *ptr = towlower(*ptr);
    ptr++;
  }

  /* MSDN claims that the function should return and set errno to
   * ERANGE, which doesn't seem to be true based on the tests. */
  *str = '\0';
  *_errno() = EINVAL;
  return EINVAL;
}