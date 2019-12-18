#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tablespaces ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/ * ts_tablespace_scan (int /*<<< orphan*/ ) ; 
 int ts_tablespaces_contain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
ts_hypertable_has_tablespace(Hypertable *ht, Oid tspc_oid)
{
	Tablespaces *tspcs = ts_tablespace_scan(ht->fd.id);

	return ts_tablespaces_contain(tspcs, tspc_oid);
}