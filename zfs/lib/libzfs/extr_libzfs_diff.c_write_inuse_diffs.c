#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ ddr_first; scalar_t__ ddr_last; } ;
typedef  TYPE_1__ dmu_diff_record_t ;
typedef  int /*<<< orphan*/  differ_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int write_inuse_diffs_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
write_inuse_diffs(FILE *fp, differ_info_t *di, dmu_diff_record_t *dr)
{
	uint64_t o;
	int err;

	for (o = dr->ddr_first; o <= dr->ddr_last; o++) {
		if ((err = write_inuse_diffs_one(fp, di, o)) != 0)
			return (err);
	}
	return (0);
}