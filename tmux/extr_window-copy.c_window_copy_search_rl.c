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
struct grid {int sx; } ;

/* Variables and functions */
 int window_copy_search_compare (struct grid*,int,int,struct grid*,int,int) ; 

__attribute__((used)) static int
window_copy_search_rl(struct grid *gd,
    struct grid *sgd, u_int *ppx, u_int py, u_int first, u_int last, int cis)
{
	u_int	ax, bx, px;
	int	matched;

	for (ax = last + 1; ax > first; ax--) {
		if (gd->sx - (ax - 1) < sgd->sx)
			continue;
		for (bx = 0; bx < sgd->sx; bx++) {
			px = ax - 1 + bx;
			matched = window_copy_search_compare(gd, px, py, sgd,
			    bx, cis);
			if (!matched)
				break;
		}
		if (bx == sgd->sx) {
			*ppx = ax - 1;
			return (1);
		}
	}
	return (0);
}