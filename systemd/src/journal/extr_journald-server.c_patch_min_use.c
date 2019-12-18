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
struct TYPE_7__ {int /*<<< orphan*/  vfs_used; } ;
struct TYPE_6__ {int /*<<< orphan*/  min_use; } ;
struct TYPE_8__ {TYPE_2__ space; TYPE_1__ metrics; } ;
typedef  TYPE_3__ JournalStorage ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 

__attribute__((used)) static void patch_min_use(JournalStorage *storage) {
        assert(storage);

        /* Let's bump the min_use limit to the current usage on disk. We do
         * this when starting up and first opening the journal files. This way
         * sudden spikes in disk usage will not cause journald to vacuum files
         * without bounds. Note that this means that only a restart of journald
         * will make it reset this value. */

        storage->metrics.min_use = MAX(storage->metrics.min_use, storage->space.vfs_used);
}