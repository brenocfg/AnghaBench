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
struct bar_data {double* data; double max; double llen; } ;

/* Variables and functions */
 int /*<<< orphan*/  move_cursor (int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
show_bar(struct bar_data* d, int i, int n)
{
  double f = d->data[i] / d->max * d->llen;

  for (int line=0; line<d->llen; line++) {
    move_cursor(d->llen+1-line, n);
    if (line < f) {
      printf("\x1b[7m ");
    }
    else if (line == 0) {
      printf("\x1b[0m_");
    }
    else {
      printf("\x1b[0m ");
    }
  }
}