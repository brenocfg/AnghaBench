#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  cur_sq_x ; 
 int /*<<< orphan*/  cur_sq_y ; 
 TYPE_1__* move_list ; 
 size_t sqnum ; 

__attribute__((used)) static long
backup()                                                  /* back up a move */
{
  sqnum--;
  if (0 <= sqnum) {
  	cur_sq_x = move_list[sqnum].x;
  	cur_sq_y = move_list[sqnum].y;
  }
  return ( sqnum );
}