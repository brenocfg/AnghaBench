#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  z_id; int /*<<< orphan*/ * z_dirlocks; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_7__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 TYPE_2__* ZTOZSB (TYPE_1__*) ; 
 int zap_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

boolean_t
zfs_dirempty(znode_t *dzp)
{
	zfsvfs_t *zfsvfs = ZTOZSB(dzp);
	uint64_t count;
	int error;

	if (dzp->z_dirlocks != NULL)
		return (B_FALSE);

	error = zap_count(zfsvfs->z_os, dzp->z_id, &count);
	if (error != 0 || count != 0)
		return (B_FALSE);

	return (B_TRUE);
}