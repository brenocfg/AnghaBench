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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void PrintPercents(const int counts[4]) {
  int s;
  const int total = counts[0] + counts[1] + counts[2] + counts[3];
  for (s = 0; s < 4; ++s) {
    fprintf(stderr, "|      %2d%%", (int)(100. * counts[s] / total + .5));
  }
  fprintf(stderr, "| %7d\n", total);
}