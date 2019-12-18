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
 int ENOMEM ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  saved_env ; 
 char** strv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free_and_replace (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int save_env(void) {
        char **l;

        l = strv_copy(environ);
        if (!l)
                return -ENOMEM;

        strv_free_and_replace(saved_env, l);
        return 0;
}