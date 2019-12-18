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
typedef  int /*<<< orphan*/  WithClauseResult ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  TS_ARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compress_hypertable_with_clause_def ; 
 int /*<<< orphan*/ * ts_with_clauses_parse (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

WithClauseResult *
ts_compress_hypertable_set_clause_parse(const List *defelems)
{
	return ts_with_clauses_parse(defelems,
								 compress_hypertable_with_clause_def,
								 TS_ARRAY_LEN(compress_hypertable_with_clause_def));
}