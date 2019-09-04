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
struct TYPE_2__ {int dir; size_t x; size_t y; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int START_SQUARE ; 
 int WALL_TOP ; 
 int /*<<< orphan*/  draw_solid_square (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enter_square (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hBrushDead ; 
 int /*<<< orphan*/  hBrushLiving ; 
 int /*<<< orphan*/  hDC ; 
 int /*<<< orphan*/  hWnd ; 
 int** maze ; 
 TYPE_1__* path ; 
 size_t pathi ; 

__attribute__((used)) static int
solve_maze()                             /* solve it with graphical feedback */
{
  int ret;
  int action_done;

  do {
    action_done = 1;
    if ( ++path[pathi].dir >= 4 ) {
      pathi--;
      draw_solid_square( (int)(path[pathi].x), (int)(path[pathi].y),
	  	       (int)(path[pathi].dir), hDC, hBrushDead);
      ret = 0;
    }
    else if ( ! (maze[path[pathi].x][path[pathi].y] &
	  	(WALL_TOP >> path[pathi].dir))  &&
	     ( (pathi == 0) || ( (path[pathi].dir !=
		  	    (int)(path[pathi-1].dir+2)%4) ) ) ) {
      enter_square(pathi, hDC, hBrushLiving);
      pathi++;
      if ( maze[path[pathi].x][path[pathi].y] & START_SQUARE ) {
	    DeleteObject(hBrushLiving);
	    DeleteObject(hBrushDead);
	    ReleaseDC(hWnd, hDC);
          ret = 1;
      } else {
        ret = 0;
      }
    } else {
      action_done = 0;
    }
  } while (! action_done);

  return ret;
}