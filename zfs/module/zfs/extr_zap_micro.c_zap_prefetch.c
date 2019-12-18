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
typedef  int /*<<< orphan*/  zap_name_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fzap_prefetch (int /*<<< orphan*/ *) ; 
 int zap_lockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * zap_name_alloc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_unlockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zap_prefetch(objset_t *os, uint64_t zapobj, const char *name)
{
	zap_t *zap;
	int err;
	zap_name_t *zn;

	err = zap_lockdir(os, zapobj, NULL, RW_READER, TRUE, FALSE, FTAG, &zap);
	if (err)
		return (err);
	zn = zap_name_alloc(zap, name, 0);
	if (zn == NULL) {
		zap_unlockdir(zap, FTAG);
		return (SET_ERROR(ENOTSUP));
	}

	fzap_prefetch(zn);
	zap_name_free(zn);
	zap_unlockdir(zap, FTAG);
	return (err);
}