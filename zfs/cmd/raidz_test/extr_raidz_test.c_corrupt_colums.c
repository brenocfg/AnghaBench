#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* rm_col; } ;
typedef  TYPE_1__ raidz_map_t ;
struct TYPE_5__ {int /*<<< orphan*/  rc_size; int /*<<< orphan*/  rc_abd; } ;
typedef  TYPE_2__ raidz_col_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rand ; 

__attribute__((used)) static void
corrupt_colums(raidz_map_t *rm, const int *tgts, const int cnt)
{
	int i;
	raidz_col_t *col;

	for (i = 0; i < cnt; i++) {
		col = &rm->rm_col[tgts[i]];
		abd_iterate_func(col->rc_abd, 0, col->rc_size, init_rand, NULL);
	}
}