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

__attribute__((used)) static int stb_not_crap(int best, int dist)
{
   return   ((best > 2  &&  dist <= 0x00100)     
          || (best > 5  &&  dist <= 0x04000)
          || (best > 7  &&  dist <= 0x80000));
}