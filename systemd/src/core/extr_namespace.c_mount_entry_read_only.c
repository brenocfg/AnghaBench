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
struct TYPE_4__ {int /*<<< orphan*/  mode; scalar_t__ read_only; } ;
typedef  TYPE_1__ MountEntry ;

/* Variables and functions */
 int /*<<< orphan*/  INACCESSIBLE ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READONLY ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

__attribute__((used)) static bool mount_entry_read_only(const MountEntry *p) {
        assert(p);

        return p->read_only || IN_SET(p->mode, READONLY, INACCESSIBLE);
}