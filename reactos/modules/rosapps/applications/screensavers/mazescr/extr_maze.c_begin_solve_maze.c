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
struct TYPE_2__ {size_t x; size_t y; int dir; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int WALL_TOP ; 
 int end_dir ; 
 size_t end_x ; 
 size_t end_y ; 
 int** maze ; 
 TYPE_1__* path ; 
 size_t pathi ; 
 int start_dir ; 
 size_t start_x ; 
 size_t start_y ; 

__attribute__((used)) static void begin_solve_maze(HWND hWnd)                             /* solve it with graphical feedback */
{
    /* plug up the surrounding wall */
    maze[start_x][start_y] |= (WALL_TOP >> start_dir);
    maze[end_x][end_y] |= (WALL_TOP >> end_dir);

    /* initialize search path */
    pathi = 0;
    path[pathi].x = end_x;
    path[pathi].y = end_y;
    path[pathi].dir = -1;
}