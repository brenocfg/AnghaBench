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
struct vacuum_candidate {struct vacuum_candidate* oldest_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vacuum_candidate*) ; 

__attribute__((used)) static void vacuum_candidate_free(struct vacuum_candidate *c) {
        if (!c)
                return;

        free(c->oldest_file);
        free(c);
}