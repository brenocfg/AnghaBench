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
 scalar_t__ _ismbblead (unsigned char const) ; 

unsigned char * _mbsninc(const unsigned char *str, size_t n)
{
  if(!str)
    return NULL;

  while (n > 0 && *str)
  {
    if (_ismbblead(*str))
    {
      if (!*(str+1))
         break;
      str++;
    }
    str++;
    n--;
  }

  return (unsigned char*)str;
}