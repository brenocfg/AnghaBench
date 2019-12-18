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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_5__ {int /*<<< orphan*/  compressed_hypertable_id; int /*<<< orphan*/  compressed; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ ts_hypertable_update (TYPE_2__*) ; 

bool
ts_hypertable_set_compressed_id(Hypertable *ht, int32 compressed_hypertable_id)
{
	Assert(!ht->fd.compressed);
	ht->fd.compressed_hypertable_id = compressed_hypertable_id;
	return ts_hypertable_update(ht) > 0;
}