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
struct TYPE_4__ {int /*<<< orphan*/  generator_late; int /*<<< orphan*/  generator_early; int /*<<< orphan*/  generator; } ;
typedef  TYPE_1__ LookupPaths ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int mkdir_p_label (int /*<<< orphan*/ ,int) ; 

int lookup_paths_mkdir_generator(LookupPaths *p) {
        int r, q;

        assert(p);

        if (!p->generator || !p->generator_early || !p->generator_late)
                return -EINVAL;

        r = mkdir_p_label(p->generator, 0755);

        q = mkdir_p_label(p->generator_early, 0755);
        if (q < 0 && r >= 0)
                r = q;

        q = mkdir_p_label(p->generator_late, 0755);
        if (q < 0 && r >= 0)
                r = q;

        return r;
}