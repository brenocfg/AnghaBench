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
struct machine_info {int /*<<< orphan*/  control_group; int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct machine_info*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero (struct machine_info) ; 

__attribute__((used)) static void machine_info_clear(struct machine_info *info) {
        assert(info);

        free(info->name);
        free(info->state);
        free(info->control_group);
        zero(*info);
}