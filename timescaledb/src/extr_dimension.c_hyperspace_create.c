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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {scalar_t__ num_dimensions; int /*<<< orphan*/  capacity; int /*<<< orphan*/  main_table_relid; int /*<<< orphan*/  hypertable_id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ Hyperspace ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERSPACE_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* MemoryContextAllocZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Hyperspace *
hyperspace_create(int32 hypertable_id, Oid main_table_relid, uint16 num_dimensions,
				  MemoryContext mctx)
{
	Hyperspace *hs = MemoryContextAllocZero(mctx, HYPERSPACE_SIZE(num_dimensions));

	hs->hypertable_id = hypertable_id;
	hs->main_table_relid = main_table_relid;
	hs->capacity = num_dimensions;
	hs->num_dimensions = 0;
	return hs;
}