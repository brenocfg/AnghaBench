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
typedef  int /*<<< orphan*/  zap_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  TRUE ; 
 int zap_lockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int zap_remove_impl (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_unlockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zap_remove_norm(objset_t *os, uint64_t zapobj, const char *name,
    matchtype_t mt, dmu_tx_t *tx)
{
	zap_t *zap;
	int err;

	err = zap_lockdir(os, zapobj, tx, RW_WRITER, TRUE, FALSE, FTAG, &zap);
	if (err)
		return (err);
	err = zap_remove_impl(zap, name, mt, tx);
	zap_unlockdir(zap, FTAG);
	return (err);
}