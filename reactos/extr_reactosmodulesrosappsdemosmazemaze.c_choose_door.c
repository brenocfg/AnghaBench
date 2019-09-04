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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int DOOR_IN_ANY ; 
 int DOOR_IN_BOTTOM ; 
 int DOOR_IN_LEFT ; 
 int DOOR_IN_RIGHT ; 
 int DOOR_IN_TOP ; 
 int DOOR_OUT_BOTTOM ; 
 int DOOR_OUT_LEFT ; 
 int DOOR_OUT_RIGHT ; 
 int DOOR_OUT_TOP ; 
 int WALL_BOTTOM ; 
 int WALL_LEFT ; 
 int WALL_RIGHT ; 
 int WALL_TOP ; 
 size_t cur_sq_x ; 
 size_t cur_sq_y ; 
 int /*<<< orphan*/  draw_wall (size_t,size_t,int,int /*<<< orphan*/ ) ; 
 size_t get_random (int) ; 
 int** maze ; 

__attribute__((used)) static int
choose_door(HDC hDC)                                    /* pick a new path */
{
  int candidates[3];
  register int num_candidates;

  num_candidates = 0;

  /* top wall */
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_IN_TOP )
    goto rightwall;
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_OUT_TOP )
    goto rightwall;
  if ( maze[cur_sq_x][cur_sq_y] & WALL_TOP )
    goto rightwall;
  if ( maze[cur_sq_x][cur_sq_y - 1] & DOOR_IN_ANY ) {
    maze[cur_sq_x][cur_sq_y] |= WALL_TOP;
    maze[cur_sq_x][cur_sq_y - 1] |= WALL_BOTTOM;
    draw_wall(cur_sq_x, cur_sq_y, 0, hDC);
    goto rightwall;
  }
  candidates[num_candidates++] = 0;

 rightwall:
  /* right wall */
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_IN_RIGHT )
    goto bottomwall;
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_OUT_RIGHT )
    goto bottomwall;
  if ( maze[cur_sq_x][cur_sq_y] & WALL_RIGHT )
    goto bottomwall;
  if ( maze[cur_sq_x + 1][cur_sq_y] & DOOR_IN_ANY ) {
    maze[cur_sq_x][cur_sq_y] |= WALL_RIGHT;
    maze[cur_sq_x + 1][cur_sq_y] |= WALL_LEFT;
    draw_wall(cur_sq_x, cur_sq_y, 1, hDC);
    goto bottomwall;
  }
  candidates[num_candidates++] = 1;

 bottomwall:
  /* bottom wall */
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_IN_BOTTOM )
    goto leftwall;
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_OUT_BOTTOM )
    goto leftwall;
  if ( maze[cur_sq_x][cur_sq_y] & WALL_BOTTOM )
    goto leftwall;
  if ( maze[cur_sq_x][cur_sq_y + 1] & DOOR_IN_ANY ) {
    maze[cur_sq_x][cur_sq_y] |= WALL_BOTTOM;
    maze[cur_sq_x][cur_sq_y + 1] |= WALL_TOP;
    draw_wall(cur_sq_x, cur_sq_y, 2, hDC);
    goto leftwall;
  }
  candidates[num_candidates++] = 2;

 leftwall:
  /* left wall */
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_IN_LEFT )
    goto donewall;
  if ( maze[cur_sq_x][cur_sq_y] & DOOR_OUT_LEFT )
    goto donewall;
  if ( maze[cur_sq_x][cur_sq_y] & WALL_LEFT )
    goto donewall;
  if ( maze[cur_sq_x - 1][cur_sq_y] & DOOR_IN_ANY ) {
    maze[cur_sq_x][cur_sq_y] |= WALL_LEFT;
    maze[cur_sq_x - 1][cur_sq_y] |= WALL_RIGHT;
    draw_wall(cur_sq_x, cur_sq_y, 3, hDC);
    goto donewall;
  }
  candidates[num_candidates++] = 3;

 donewall:
  if (num_candidates == 0)
    return ( -1 );
  if (num_candidates == 1)
    return ( candidates[0] );
  return ( candidates[ get_random(num_candidates) ] );

}