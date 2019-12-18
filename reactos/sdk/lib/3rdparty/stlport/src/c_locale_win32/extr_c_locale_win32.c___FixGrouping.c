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
 int /*<<< orphan*/  CHAR_MAX ; 

void __FixGrouping(char *grouping) {
  /* This converts NT version which uses '0' instead of 0, etc ; to ANSI */
  char *g = grouping;
  char building_group = 0;
  char repeat_last = 0;
  /* Check there is a grouping info otherwise we would add a useless CHAR_MAX */
  if (*g) {
    for (; *g; ++g) {
      if (*g > '0' && *g <= '9') {
        if (!building_group) {
          *grouping = *g - '0';
          building_group = 1;
        }
        else {
          /* Known issue: grouping might roll. */
          *grouping = *grouping * 10 + *g - '0';
        }
      }
      else if (*g == '0') {
        if (!building_group) {
          repeat_last = 1;
        }
        else
          /* Known issue: grouping might roll. */
          *grouping *= 10;
      }
      else if (*g == ';') {
        /* Stop adding to the current group */
        building_group = 0;
        ++grouping;
      }
      /* else we ignore the character */
    }

    if (!repeat_last)
      *grouping++ = CHAR_MAX;
    *grouping = 0;
  }
}