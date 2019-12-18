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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {int /*<<< orphan*/  backendId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  pid; scalar_t__ isBackgroundWorker; } ;
typedef  TYPE_2__ PGPROC ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* BackendIdGetProc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* GetLockConflicts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ VirtualTransactionIdIsValid (TYPE_1__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lock_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_cancel_backend ; 

__attribute__((used)) static void
get_job_lock_for_delete(int32 job_id)
{
	LOCKTAG tag;
	bool got_lock;

	/* Try getting an exclusive lock on the tuple in a non-blocking manner. Note this is the
	 * equivalent of a row-based FOR UPDATE lock */
	got_lock = lock_job(job_id,
						AccessExclusiveLock,
						/* session_lock */ false,
						&tag,
						/* block */ false);
	if (!got_lock)
	{
		/* If I couldn't get a lock, try killing the background worker that's running the job.
		 * This is probably not bulletproof but best-effort is good enough here. */
		VirtualTransactionId *vxid = GetLockConflicts(&tag, AccessExclusiveLock);
		PGPROC *proc;

		if (VirtualTransactionIdIsValid(*vxid))
		{
			proc = BackendIdGetProc(vxid->backendId);
			if (proc != NULL && proc->isBackgroundWorker)
			{
				elog(NOTICE,
					 "cancelling the background worker for job %d (pid %d)",
					 job_id,
					 proc->pid);
				DirectFunctionCall1(pg_cancel_backend, Int32GetDatum(proc->pid));
			}
		}

		/* We have to grab this lock before proceeding so grab it in a blocking manner now */
		got_lock = lock_job(job_id,
							AccessExclusiveLock,
							/* session lock */ false,
							&tag,
							/* block */ true);
	}
	Assert(got_lock);
}