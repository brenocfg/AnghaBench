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

/* Variables and functions */
 int acquire_esp (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arg_esp_path ; 
 int install_random_seed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_everything () ; 

__attribute__((used)) static int verb_random_seed(int argc, char *argv[], void *userdata) {
        int r;

        r = acquire_esp(false, NULL, NULL, NULL, NULL);
        if (r < 0)
                return r;

        r = install_random_seed(arg_esp_path);
        if (r < 0)
                return r;

        (void) sync_everything();
        return 0;
}