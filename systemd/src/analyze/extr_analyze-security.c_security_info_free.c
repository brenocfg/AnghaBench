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
struct security_info {int /*<<< orphan*/  system_call_filter; int /*<<< orphan*/  system_call_architectures; int /*<<< orphan*/  supplementary_groups; int /*<<< orphan*/  device_policy; int /*<<< orphan*/  notify_access; int /*<<< orphan*/  keyring_mode; int /*<<< orphan*/  root_image; int /*<<< orphan*/  root_directory; int /*<<< orphan*/  protect_system; int /*<<< orphan*/  protect_home; int /*<<< orphan*/  user; int /*<<< orphan*/  fragment_path; int /*<<< orphan*/  load_state; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void security_info_free(struct security_info *i) {
        if (!i)
                return;

        free(i->id);
        free(i->type);
        free(i->load_state);
        free(i->fragment_path);

        free(i->user);

        free(i->protect_home);
        free(i->protect_system);

        free(i->root_directory);
        free(i->root_image);

        free(i->keyring_mode);
        free(i->notify_access);

        free(i->device_policy);

        strv_free(i->supplementary_groups);
        strv_free(i->system_call_architectures);

        set_free_free(i->system_call_filter);
}