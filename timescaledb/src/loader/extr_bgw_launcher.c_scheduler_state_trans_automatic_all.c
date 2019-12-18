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
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  DbHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scheduler_state_trans_automatic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scheduler_state_trans_automatic_all(HTAB *db_htab)
{
	HASH_SEQ_STATUS hash_seq;
	DbHashEntry *current_entry;

	hash_seq_init(&hash_seq, db_htab);
	while ((current_entry = hash_seq_search(&hash_seq)) != NULL)
		scheduler_state_trans_automatic(current_entry);
}