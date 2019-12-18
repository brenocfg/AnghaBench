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
struct TYPE_4__ {void* options_malloc; void* source_malloc; void* path_malloc; } ;
typedef  TYPE_1__ MountEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* mfree (void*) ; 

__attribute__((used)) static void mount_entry_done(MountEntry *p) {
        assert(p);

        p->path_malloc = mfree(p->path_malloc);
        p->source_malloc = mfree(p->source_malloc);
        p->options_malloc = mfree(p->options_malloc);
}