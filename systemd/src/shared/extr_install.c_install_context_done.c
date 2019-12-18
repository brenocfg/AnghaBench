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
struct TYPE_4__ {void* have_processed; void* will_process; } ;
typedef  TYPE_1__ InstallContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  install_info_free ; 
 void* ordered_hashmap_free_with_destructor (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void install_context_done(InstallContext *c) {
        assert(c);

        c->will_process = ordered_hashmap_free_with_destructor(c->will_process, install_info_free);
        c->have_processed = ordered_hashmap_free_with_destructor(c->have_processed, install_info_free);
}