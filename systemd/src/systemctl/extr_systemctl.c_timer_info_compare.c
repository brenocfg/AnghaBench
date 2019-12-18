#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_info {int /*<<< orphan*/  id; int /*<<< orphan*/  next_elapse; scalar_t__ machine; } ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct timer_info const*) ; 
 int strcasecmp (scalar_t__,scalar_t__) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer_info_compare(const struct timer_info *a, const struct timer_info *b) {
        int r;

        assert(a);
        assert(b);

        if (!a->machine && b->machine)
                return -1;
        if (a->machine && !b->machine)
                return 1;
        if (a->machine && b->machine) {
                r = strcasecmp(a->machine, b->machine);
                if (r != 0)
                        return r;
        }

        r = CMP(a->next_elapse, b->next_elapse);
        if (r != 0)
                return r;

        return strcmp(a->id, b->id);
}