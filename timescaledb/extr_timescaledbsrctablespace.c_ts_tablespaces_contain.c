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
struct TYPE_5__ {int num_tablespaces; TYPE_1__* tablespaces; } ;
typedef  TYPE_2__ Tablespaces ;
struct TYPE_4__ {scalar_t__ tablespace_oid; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */

bool
ts_tablespaces_contain(Tablespaces *tspcs, Oid tspc_oid)
{
	int i;

	for (i = 0; i < tspcs->num_tablespaces; i++)
		if (tspc_oid == tspcs->tablespaces[i].tablespace_oid)
			return true;

	return false;
}