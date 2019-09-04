#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_4__ {scalar_t__ is_default; } ;
typedef  TYPE_1__ WithClauseResult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 size_t ContinuousViewOptionRefreshLag ; 
 int continuous_agg_parse_refresh_lag (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int64
get_refresh_lag(Oid column_type, int64 bucket_width, WithClauseResult *with_clause_options)
{
	if (with_clause_options[ContinuousViewOptionRefreshLag].is_default)
		return bucket_width * 2;
	return continuous_agg_parse_refresh_lag(column_type, with_clause_options);
}