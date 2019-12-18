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
struct TYPE_4__ {char const* source_const; scalar_t__ source_malloc; } ;
typedef  TYPE_1__ MountEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

__attribute__((used)) static const char *mount_entry_source(const MountEntry *p) {
        assert(p);

        return p->source_malloc ?: p->source_const;
}