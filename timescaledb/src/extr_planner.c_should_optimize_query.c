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
 int /*<<< orphan*/  ts_guc_disable_optimizations ; 
 scalar_t__ ts_guc_optimize_non_hypertables ; 

__attribute__((used)) static inline bool
should_optimize_query(Hypertable *ht)
{
	return !ts_guc_disable_optimizations && (ts_guc_optimize_non_hypertables || ht != NULL);
}