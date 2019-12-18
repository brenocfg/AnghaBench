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
typedef  scalar_t__ uint8 ;

/* Variables and functions */

__attribute__((used)) static int is24on(uint8 * data, int x, int y)
{
  uint8 r, g, b;
  int start;

  if (data == 0)
  {
    return 0;
  }
  start = y * 32 * 3 + x * 3;
  r = data[start];
  g = data[start + 1];
  b = data[start + 2];
  return !((r == 0) && (g == 0) && (b == 0));
}