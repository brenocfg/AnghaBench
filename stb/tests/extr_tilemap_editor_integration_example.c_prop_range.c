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
 scalar_t__ is_platform (short*) ; 

__attribute__((used)) static float prop_range(int n, short *tiles, int is_max)
{
   if (is_platform(tiles)) {
      static float ranges[8][2] = {
         {   0,  1 }, // phantom-flag, range is ignored
         { -15, 15 }, // x_adjust
         { -15, 15 }, // y_adjust
         {   0,  6 }, // width
         {   0, 10 }, // lspeed
         {   0, 10 }, // rspeed
         {   0,  1 }, // autoreturn, range is ignored
         {   0,  1 }, // one-shot, range is ignored
      };
      return ranges[n][is_max];
   }
   return 0;
}