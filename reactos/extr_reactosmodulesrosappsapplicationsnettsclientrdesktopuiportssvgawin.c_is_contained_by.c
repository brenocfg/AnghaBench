#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ x; scalar_t__ y; scalar_t__ cx; scalar_t__ cy; } ;
typedef  TYPE_1__ myrect ;

/* Variables and functions */

int is_contained_by(myrect* r1, myrect* r2)
{
  if (r1->x >= r2->x &&
      r1->y >= r2->y &&
      r1->x + r1->cx <= r2->x + r2->cx &&
      r1->y + r1->cy <= r2->y + r2->cy)
    return 1;
  else
    return 0;
}