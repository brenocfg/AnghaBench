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
struct TYPE_3__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_constraint_hypertable_constraint_name ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int Natts_chunk_constraint ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bool
hypertable_constraint_matches_tuple(TupleInfo *ti, const char *hypertable_constraint_name)
{
	bool nulls[Natts_chunk_constraint];
	Datum values[Natts_chunk_constraint];
	const char *constrname;

	heap_deform_tuple(ti->tuple, ti->desc, values, nulls);

	if (nulls[AttrNumberGetAttrOffset(Anum_chunk_constraint_hypertable_constraint_name)])
		return false;

	constrname = NameStr(*DatumGetName(
		values[AttrNumberGetAttrOffset(Anum_chunk_constraint_hypertable_constraint_name)]));

	if (strcmp(hypertable_constraint_name, constrname) == 0)
		return true;

	return false;
}