#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ perpetual; } ;
struct TYPE_6__ {int /*<<< orphan*/  proc_flags; } ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOUNT_PROC_IS_MOUNTED ; 
 TYPE_4__* UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static bool mount_is_mounted(Mount *m) {
        assert(m);

        return UNIT(m)->perpetual || FLAGS_SET(m->proc_flags, MOUNT_PROC_IS_MOUNTED);
}