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
typedef  int /*<<< orphan*/  u_int ;
struct utf8_data {int size; scalar_t__ width; scalar_t__* data; } ;
struct grid_cell {struct utf8_data data; } ;
struct grid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_get_cell (struct grid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct grid_cell*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ tolower (scalar_t__) ; 

__attribute__((used)) static int
window_copy_search_compare(struct grid *gd, u_int px, u_int py,
    struct grid *sgd, u_int spx, int cis)
{
	struct grid_cell	 gc, sgc;
	const struct utf8_data	*ud, *sud;

	grid_get_cell(gd, px, py, &gc);
	ud = &gc.data;
	grid_get_cell(sgd, spx, 0, &sgc);
	sud = &sgc.data;

	if (ud->size != sud->size || ud->width != sud->width)
		return (0);

	if (cis && ud->size == 1)
		return (tolower(ud->data[0]) == sud->data[0]);

	return (memcmp(ud->data, sud->data, ud->size) == 0);
}