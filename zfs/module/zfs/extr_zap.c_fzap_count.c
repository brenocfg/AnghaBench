#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zap_num_entries_mtx; } ;
struct TYPE_7__ {TYPE_1__ zap_f; int /*<<< orphan*/  zap_ismicro; } ;
typedef  TYPE_2__ zap_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  zap_num_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_3__* zap_f_phys (TYPE_2__*) ; 

int
fzap_count(zap_t *zap, uint64_t *count)
{
	ASSERT(!zap->zap_ismicro);
	mutex_enter(&zap->zap_f.zap_num_entries_mtx); /* unnecessary */
	*count = zap_f_phys(zap)->zap_num_entries;
	mutex_exit(&zap->zap_f.zap_num_entries_mtx);
	return (0);
}