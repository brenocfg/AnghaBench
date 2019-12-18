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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int ENOENT ; 
 int zap_lookup (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,scalar_t__*) ; 
 int zap_remove (int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int zap_update (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 

int
zap_increment(objset_t *os, uint64_t obj, const char *name, int64_t delta,
    dmu_tx_t *tx)
{
	uint64_t value = 0;

	if (delta == 0)
		return (0);

	int err = zap_lookup(os, obj, name, 8, 1, &value);
	if (err != 0 && err != ENOENT)
		return (err);
	value += delta;
	if (value == 0)
		err = zap_remove(os, obj, name, tx);
	else
		err = zap_update(os, obj, name, 8, 1, &value, tx);
	return (err);
}