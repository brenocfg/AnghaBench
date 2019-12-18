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
 scalar_t__ _ismbblead (unsigned int const) ; 
 scalar_t__ _ismbbtrail (unsigned int const) ; 

size_t _mbclen2(const unsigned int s)
{
  return (_ismbblead(s>>8) && _ismbbtrail(s&0x00FF)) ? 2 : 1;
}