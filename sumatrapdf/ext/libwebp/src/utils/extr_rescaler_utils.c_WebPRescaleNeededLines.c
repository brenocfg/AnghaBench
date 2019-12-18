#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int y_accum; int y_sub; } ;
typedef  TYPE_1__ WebPRescaler ;

/* Variables and functions */

int WebPRescaleNeededLines(const WebPRescaler* const wrk, int max_num_lines) {
  const int num_lines = (wrk->y_accum + wrk->y_sub - 1) / wrk->y_sub;
  return (num_lines > max_num_lines) ? max_num_lines : num_lines;
}