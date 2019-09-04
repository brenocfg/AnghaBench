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
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  ContinuousAggsCacheInvalEntry ;

/* Variables and functions */
 int /*<<< orphan*/  cache_inval_entry_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  continuous_aggs_cache_inval_htab ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cache_inval_htab_write(void)
{
	HASH_SEQ_STATUS hash_seq;
	ContinuousAggsCacheInvalEntry *current_entry;

	hash_seq_init(&hash_seq, continuous_aggs_cache_inval_htab);
	while ((current_entry = hash_seq_search(&hash_seq)) != NULL)
		cache_inval_entry_write(current_entry);
}