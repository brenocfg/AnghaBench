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
typedef  int u_int ;
struct screen {int dummy; } ;

/* Variables and functions */
 int screen_hsize (struct screen*) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 

__attribute__((used)) static void
window_copy_move_right(struct screen *s, u_int *fx, u_int *fy, int wrapflag)
{
	if (*fx == screen_size_x(s) - 1) { /* right */
		if (*fy == screen_hsize(s) + screen_size_y(s)) { /* bottom */
			if (wrapflag) {
				*fx = 0;
				*fy = 0;
			}
			return;
		}
		*fx = 0;
		*fy = *fy + 1;
	} else
		*fx = *fx + 1;
}