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
typedef  scalar_t__ u_int ;
struct screen {int dummy; } ;

/* Variables and functions */
 scalar_t__ screen_hsize (struct screen*) ; 
 scalar_t__ screen_size_x (struct screen*) ; 
 scalar_t__ screen_size_y (struct screen*) ; 

__attribute__((used)) static void
window_copy_move_left(struct screen *s, u_int *fx, u_int *fy, int wrapflag)
{
	if (*fx == 0) {	/* left */
		if (*fy == 0) { /* top */
			if (wrapflag) {
				*fx = screen_size_x(s) - 1;
				*fy = screen_hsize(s) + screen_size_y(s);
			}
			return;
		}
		*fx = screen_size_x(s) - 1;
		*fy = *fy - 1;
	} else
		*fx = *fx - 1;
}