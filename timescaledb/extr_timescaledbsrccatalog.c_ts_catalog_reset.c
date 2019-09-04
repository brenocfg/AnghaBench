#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int initialized; } ;
struct TYPE_3__ {int /*<<< orphan*/  database_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 TYPE_2__ catalog ; 
 TYPE_1__ database_info ; 

void
ts_catalog_reset(void)
{
	catalog.initialized = false;
	database_info.database_id = InvalidOid;
}