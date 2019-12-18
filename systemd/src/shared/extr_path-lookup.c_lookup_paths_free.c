#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* temporary_dir; void* root_dir; void* runtime_control; void* persistent_control; void* transient; void* generator_late; void* generator_early; void* generator; void* runtime_attached; void* persistent_attached; void* runtime_config; void* persistent_config; int /*<<< orphan*/  search_path; } ;
typedef  TYPE_1__ LookupPaths ;

/* Variables and functions */
 void* mfree (void*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

void lookup_paths_free(LookupPaths *p) {
        if (!p)
                return;

        p->search_path = strv_free(p->search_path);

        p->persistent_config = mfree(p->persistent_config);
        p->runtime_config = mfree(p->runtime_config);

        p->persistent_attached = mfree(p->persistent_attached);
        p->runtime_attached = mfree(p->runtime_attached);

        p->generator = mfree(p->generator);
        p->generator_early = mfree(p->generator_early);
        p->generator_late = mfree(p->generator_late);

        p->transient = mfree(p->transient);

        p->persistent_control = mfree(p->persistent_control);
        p->runtime_control = mfree(p->runtime_control);

        p->root_dir = mfree(p->root_dir);
        p->temporary_dir = mfree(p->temporary_dir);
}