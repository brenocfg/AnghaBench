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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int rm_firstdatacol; int rm_cols; TYPE_1__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_4__ {scalar_t__ rc_size; int /*<<< orphan*/ * rc_abd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MIN (scalar_t__,scalar_t__) ; 
 size_t VDEV_RAIDZ_P ; 
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  abd_iterate_func2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_to_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_raidz_reconst_p_func ; 

__attribute__((used)) static int
vdev_raidz_reconstruct_p(raidz_map_t *rm, int *tgts, int ntgts)
{
	int x = tgts[0];
	int c;
	abd_t *dst, *src;

	ASSERT(ntgts == 1);
	ASSERT(x >= rm->rm_firstdatacol);
	ASSERT(x < rm->rm_cols);

	ASSERT(rm->rm_col[x].rc_size <= rm->rm_col[VDEV_RAIDZ_P].rc_size);
	ASSERT(rm->rm_col[x].rc_size > 0);

	src = rm->rm_col[VDEV_RAIDZ_P].rc_abd;
	dst = rm->rm_col[x].rc_abd;

	abd_copy_from_buf(dst, abd_to_buf(src), rm->rm_col[x].rc_size);

	for (c = rm->rm_firstdatacol; c < rm->rm_cols; c++) {
		uint64_t size = MIN(rm->rm_col[x].rc_size,
		    rm->rm_col[c].rc_size);

		src = rm->rm_col[c].rc_abd;
		dst = rm->rm_col[x].rc_abd;

		if (c == x)
			continue;

		(void) abd_iterate_func2(dst, src, 0, 0, size,
		    vdev_raidz_reconst_p_func, NULL);
	}

	return (1 << VDEV_RAIDZ_P);
}