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
 scalar_t__ _ismbslead (unsigned char const*,unsigned char const*) ; 

int _ismbstrail( const unsigned char *start, const unsigned char *str)
{
  /* Note: this function doesn't check _ismbbtrail */
  if ((str > start) && _ismbslead(start, str-1))
    return -1;
  else
    return 0;
}