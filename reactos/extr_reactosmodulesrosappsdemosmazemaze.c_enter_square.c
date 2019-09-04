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
struct TYPE_2__ {int dir; scalar_t__ y; scalar_t__ x; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  draw_solid_square (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* path ; 

__attribute__((used)) static void
enter_square(int n, HDC hDC, HBRUSH hBrush)  /* move into a neighboring square */
{
  draw_solid_square( (int)path[n].x, (int)path[n].y,
		    (int)path[n].dir, hDC, hBrush);

  path[n+1].dir = -1;
  switch (path[n].dir) {
  case 0: path[n+1].x = path[n].x;
    path[n+1].y = path[n].y - 1;
    break;
  case 1: path[n+1].x = path[n].x + 1;
    path[n+1].y = path[n].y;
    break;
  case 2: path[n+1].x = path[n].x;
    path[n+1].y = path[n].y + 1;
    break;
  case 3: path[n+1].x = path[n].x - 1;
    path[n+1].y = path[n].y;
    break;
  }
}