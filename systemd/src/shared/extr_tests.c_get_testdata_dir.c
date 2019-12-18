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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  F_OK ; 
 char* SYSTEMD_TEST_DATA ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  load_testdata_env () ; 
 int /*<<< orphan*/  stderr ; 

const char* get_testdata_dir(void) {
        const char *env;

        load_testdata_env();

        /* if the env var is set, use that */
        env = getenv("SYSTEMD_TEST_DATA");
        if (!env)
                env = SYSTEMD_TEST_DATA;
        if (access(env, F_OK) < 0) {
                fprintf(stderr, "ERROR: $SYSTEMD_TEST_DATA directory [%s] does not exist\n", env);
                exit(EXIT_FAILURE);
        }

        return env;
}