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
typedef  int uint8_t ;

/* Variables and functions */

uint8_t
cdio_to_bcd8 (uint8_t n)
{
  /*cdio_assert (n < 100);*/

  return ((n/10)<<4) | (n%10);
}