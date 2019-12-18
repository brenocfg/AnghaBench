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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_3__ {int /*<<< orphan*/  parsed; int /*<<< orphan*/  is_default; } ;
typedef  TYPE_1__ WithClauseResult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t ContinuousViewOptionRefreshLag ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_interval (char*,int /*<<< orphan*/ ,char*) ; 

int64
continuous_agg_parse_refresh_lag(Oid column_type, WithClauseResult *with_clause_options)
{
	char *value;

	Assert(!with_clause_options[ContinuousViewOptionRefreshLag].is_default);

	value = TextDatumGetCString(with_clause_options[ContinuousViewOptionRefreshLag].parsed);

	return parse_interval(value, column_type, "refresh_lag");
}