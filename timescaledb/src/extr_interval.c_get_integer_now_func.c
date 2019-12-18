#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  integer_now_func; int /*<<< orphan*/  integer_now_func_schema; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_INTEGER_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noarg_integer_now_func_filter ; 
 int /*<<< orphan*/  ts_dimension_get_partition_type (TYPE_2__*) ; 
 int /*<<< orphan*/  ts_lookup_proc_filtered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
get_integer_now_func(Dimension *open_dim)
{
	Oid rettype;
	Oid now_func;

	rettype = ts_dimension_get_partition_type(open_dim);

	Assert(IS_INTEGER_TYPE(rettype));

	now_func = ts_lookup_proc_filtered(NameStr(open_dim->fd.integer_now_func_schema),
									   NameStr(open_dim->fd.integer_now_func),
									   NULL,
									   noarg_integer_now_func_filter,
									   &rettype);
	return now_func;
}