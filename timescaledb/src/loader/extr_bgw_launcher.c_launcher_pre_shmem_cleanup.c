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
struct TYPE_3__ {int /*<<< orphan*/ * db_scheduler_handle; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  TYPE_1__ DbHashEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate_background_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_bgw_message_queue_shmem_cleanup () ; 

__attribute__((used)) static void
launcher_pre_shmem_cleanup(int code, Datum arg)
{
	HTAB *db_htab = *(HTAB **) DatumGetPointer(arg);
	HASH_SEQ_STATUS hash_seq;
	DbHashEntry *current_entry;

	/* db_htab will be NULL if we fail during init_database_htab */
	if (db_htab != NULL)
	{
		hash_seq_init(&hash_seq, db_htab);

		/*
		 * Stop everyone (or at least tell the Postmaster we don't care about
		 * them anymore)
		 */
		while ((current_entry = hash_seq_search(&hash_seq)) != NULL)
		{
			if (current_entry->db_scheduler_handle != NULL)
			{
				terminate_background_worker(current_entry->db_scheduler_handle);
				pfree(current_entry->db_scheduler_handle);
			}
		}

		hash_destroy(db_htab);
	}

	/*
	 * Reset our pid in the queue so that others know we've died and don't
	 * wait forever
	 */
	ts_bgw_message_queue_shmem_cleanup();
}