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
typedef  int /*<<< orphan*/  Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  indexing_create_and_verify_hypertable_indexes (int /*<<< orphan*/ *,int,int) ; 

void
ts_indexing_create_default_indexes(Hypertable *ht)
{
	indexing_create_and_verify_hypertable_indexes(ht, true, false);
}