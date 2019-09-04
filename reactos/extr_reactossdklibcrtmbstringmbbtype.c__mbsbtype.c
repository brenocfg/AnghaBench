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
 int _MBC_ILLEGAL ; 
 int _MBC_LEAD ; 
 int _MBC_SINGLE ; 
 int _MBC_TRAIL ; 
 scalar_t__ _ismbblead (unsigned char const) ; 
 scalar_t__ _ismbbtrail (unsigned char const) ; 

int _mbsbtype( const unsigned char *str, size_t n )
{
  int lead = 0;
  const unsigned char *end = str + n;

  /* Lead bytes can also be trail bytes so we need to analyse the string.
   * Also we must return _MBC_ILLEGAL for chars past the end of the string
   */
  while (str < end) /* Note: we skip the last byte - will check after the loop */
  {
    if (!*str)
      return _MBC_ILLEGAL;
    lead = !lead && _ismbblead(*str);
    str++;
  }

  if (lead)
    if (_ismbbtrail(*str))
      return _MBC_TRAIL;
    else
      return _MBC_ILLEGAL;
  else
    if (_ismbblead(*str))
      return _MBC_LEAD;
    else
      return _MBC_SINGLE;
}