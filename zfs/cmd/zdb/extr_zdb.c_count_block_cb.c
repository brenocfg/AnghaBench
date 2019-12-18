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
typedef  int /*<<< orphan*/  zdb_cb_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkbuf ;

/* Variables and functions */
 int BP_SPRINTF_LEN ; 
 int /*<<< orphan*/  ZDB_OT_DEFERRED ; 
 int* dump_opt ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf_blkptr (char*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zdb_count_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
count_block_cb(void *arg, const blkptr_t *bp, dmu_tx_t *tx)
{
	zdb_cb_t *zcb = arg;

	if (dump_opt['b'] >= 5) {
		char blkbuf[BP_SPRINTF_LEN];
		snprintf_blkptr(blkbuf, sizeof (blkbuf), bp);
		(void) printf("[%s] %s\n",
		    "deferred free", blkbuf);
	}
	zdb_count_block(zcb, NULL, bp, ZDB_OT_DEFERRED);
	return (0);
}