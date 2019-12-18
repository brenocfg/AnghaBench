#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/ * chunk_append; } ;
typedef  int /*<<< orphan*/  TSLWLocks ;
typedef  int /*<<< orphan*/  LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  AddinShmemInitLock ; 
 int /*<<< orphan*/  CHUNK_APPEND_LWLOCK_TRANCHE_NAME ; 
 TYPE_4__* GetNamedLWLockTranche (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  RENDEZVOUS_CHUNK_APPEND_LWLOCK ; 
 TYPE_1__* ShmemInitStruct (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  TS_LWLOCKS_SHMEM_NAME ; 
 scalar_t__ find_rendezvous_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ts_lwlocks ; 

void
ts_lwlocks_shmem_startup()
{
	bool found;
	LWLock **lock_pointer;

	LWLockAcquire(AddinShmemInitLock, LW_EXCLUSIVE);
	ts_lwlocks = ShmemInitStruct(TS_LWLOCKS_SHMEM_NAME, sizeof(TSLWLocks), &found);
	if (!found)
	{
		memset(ts_lwlocks, 0, sizeof(TSLWLocks));
		ts_lwlocks->chunk_append = &(GetNamedLWLockTranche(CHUNK_APPEND_LWLOCK_TRANCHE_NAME))->lock;
	}
	LWLockRelease(AddinShmemInitLock);

	/*
	 * We use a lock specific rendezvous variable to decouple the struct
	 * from the individual lock users to have no constraints on the struct
	 * across timescaledb versions.
	 */
	lock_pointer = (LWLock **) find_rendezvous_variable(RENDEZVOUS_CHUNK_APPEND_LWLOCK);
	*lock_pointer = ts_lwlocks->chunk_append;
}