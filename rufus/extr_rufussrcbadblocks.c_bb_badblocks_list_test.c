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
typedef  int /*<<< orphan*/  blk64_t ;
typedef  int /*<<< orphan*/  bb_u64_list ;
typedef  scalar_t__ bb_badblocks_list ;

/* Variables and functions */
 int bb_u64_list_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bb_badblocks_list_test(bb_badblocks_list bb, blk64_t blk)
{
	return bb_u64_list_test((bb_u64_list) bb, blk);
}