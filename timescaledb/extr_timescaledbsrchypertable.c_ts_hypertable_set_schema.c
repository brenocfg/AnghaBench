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
struct TYPE_5__ {int /*<<< orphan*/  schema_name; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int ts_hypertable_update (TYPE_2__*) ; 

int
ts_hypertable_set_schema(Hypertable *ht, const char *newname)
{
	namestrcpy(&ht->fd.schema_name, newname);

	return ts_hypertable_update(ht);
}