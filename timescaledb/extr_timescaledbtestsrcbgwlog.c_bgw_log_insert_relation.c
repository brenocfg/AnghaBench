#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_2__ {scalar_t__ current_time; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 char* application_name ; 
 int /*<<< orphan*/  ts_catalog_insert_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* ts_params_get () ; 

__attribute__((used)) static bool
bgw_log_insert_relation(Relation rel, char *msg)
{
	TupleDesc desc = RelationGetDescr(rel);
	static int32 msg_no = 0;
	Datum values[4];
	bool nulls[4] = { false, false, false };

	values[0] = Int32GetDatum(msg_no++);
	values[1] = Int64GetDatum((int64) ts_params_get()->current_time);
	values[2] = CStringGetTextDatum(application_name);
	values[3] = CStringGetTextDatum(msg);

	ts_catalog_insert_values(rel, desc, values, nulls);

	return true;
}