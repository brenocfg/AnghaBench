#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t x; size_t y; int dir; } ;
struct TYPE_3__ {size_t x; size_t y; int dir; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int DOOR_IN_TOP ; 
 int DOOR_OUT_TOP ; 
 int END_SQUARE ; 
 int backup () ; 
 int choose_door (int /*<<< orphan*/ ) ; 
 size_t cur_sq_x ; 
 size_t cur_sq_y ; 
 int /*<<< orphan*/  hDC ; 
 int** maze ; 
 TYPE_2__* move_list ; 
 int path_length ; 
 TYPE_1__* save_path ; 
 size_t sqnum ; 

__attribute__((used)) static void create_maze(HWND hWnd)             /* create a maze layout given the initialized maze */
{
    register int i, newdoor = 0;

    do {
        move_list[sqnum].x = cur_sq_x;
        move_list[sqnum].y = cur_sq_y;
        move_list[sqnum].dir = newdoor;
        while ((newdoor = choose_door(hDC)) == -1) { /* pick a door */
            if (backup() == -1) { /* no more doors ... backup */
                return; /* done ... return */
            }
        }

        /* mark the out door */
        maze[cur_sq_x][cur_sq_y] |= (DOOR_OUT_TOP >> newdoor);

        switch (newdoor) {
        case 0: cur_sq_y--;
            break;
        case 1: cur_sq_x++;
            break;
        case 2: cur_sq_y++;
            break;
        case 3: cur_sq_x--;
            break;
        }
        sqnum++;

        /* mark the in door */
        maze[cur_sq_x][cur_sq_y] |= (DOOR_IN_TOP >> ((newdoor + 2) % 4));

        /* if end square set path length and save path */
        if (maze[cur_sq_x][cur_sq_y] & END_SQUARE) {
            path_length = sqnum;
            for (i = 0; i < path_length; i++) {
                save_path[i].x = move_list[i].x;
                save_path[i].y = move_list[i].y;
                save_path[i].dir = move_list[i].dir;
            }
        }
    } while (1);
}