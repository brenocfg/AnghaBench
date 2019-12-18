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
struct bar_data {scalar_t__ tlen; int col; int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  erase_cursor () ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_cursor (int,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
show_title(struct bar_data* d)
{
  int start;

  erase_cursor();
  clear();
  if (d->tlen == 0) return;
  start = (d->col - d->tlen) / 2;
  move_cursor(1, start);
  fwrite(d->title, d->tlen, 1, stdout);
}