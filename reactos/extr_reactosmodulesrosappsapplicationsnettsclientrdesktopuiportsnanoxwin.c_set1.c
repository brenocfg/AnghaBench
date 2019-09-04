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
typedef  int uint8 ;

/* Variables and functions */

__attribute__((used)) static void set1(uint8 * data, int x, int y)
{
  int start;
  int shift;

  if (data == 0)
  {
    return;
  }
  start = (y * 32) / 8 + x / 8;
  shift = x % 8;
  data[start] = data[start] | (0x80 >> shift);
}