#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zap_num_entries; } ;
struct TYPE_13__ {TYPE_2__ zap_m; TYPE_1__* zap_dbuf; scalar_t__ zap_ismicro; } ;
typedef  TYPE_3__ zap_t ;
struct TYPE_14__ {int zs_num_blocks; int /*<<< orphan*/  zs_num_entries; int /*<<< orphan*/  zs_blocksize; } ;
typedef  TYPE_4__ zap_stats_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_11__ {int /*<<< orphan*/  db_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  fzap_get_stats (TYPE_3__*,TYPE_4__*) ; 
 int zap_lockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  zap_unlockdir (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
zap_get_stats(objset_t *os, uint64_t zapobj, zap_stats_t *zs)
{
	zap_t *zap;

	int err =
	    zap_lockdir(os, zapobj, NULL, RW_READER, TRUE, FALSE, FTAG, &zap);
	if (err != 0)
		return (err);

	bzero(zs, sizeof (zap_stats_t));

	if (zap->zap_ismicro) {
		zs->zs_blocksize = zap->zap_dbuf->db_size;
		zs->zs_num_entries = zap->zap_m.zap_num_entries;
		zs->zs_num_blocks = 1;
	} else {
		fzap_get_stats(zap, zs);
	}
	zap_unlockdir(zap, FTAG);
	return (0);
}