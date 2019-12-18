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
struct bar_data {int llen; int dlen; int max; } ;

/* Variables and functions */
 int /*<<< orphan*/  move_cursor (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
show_yaxis(struct bar_data* d)
{
  move_cursor(1,2);
  printf("\x1b[0m");
  for (int i=0; i<d->llen; i++) {
    move_cursor(i+2, d->dlen+1);
    if (i == 0) {
      printf("├ %d   ", d->max);
    }
    else if (i == d->llen-1) {
      printf("├ 0");
    }
    else {
      printf("│");
    }
  }
}