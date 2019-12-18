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
 int /*<<< orphan*/  REPLACE_ENV_USE_ENVIRONMENT ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int streq (int /*<<< orphan*/ ,char*) ; 
 int streq_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_env_get_n (char**,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_env_strv_get_n(void) {
        const char *_env[] = {
                "FOO=NO NO NO",
                "FOO=BAR BAR",
                "BAR=waldo",
                "PATH=unset",
                NULL
        };
        char **env = (char**) _env;

        assert_se(streq(strv_env_get_n(env, "FOO__", 3, 0), "BAR BAR"));
        assert_se(streq(strv_env_get_n(env, "FOO__", 3, REPLACE_ENV_USE_ENVIRONMENT), "BAR BAR"));
        assert_se(streq(strv_env_get_n(env, "FOO", 3, 0), "BAR BAR"));
        assert_se(streq(strv_env_get_n(env, "FOO", 3, REPLACE_ENV_USE_ENVIRONMENT), "BAR BAR"));

        assert_se(streq(strv_env_get_n(env, "PATH__", 4, 0), "unset"));
        assert_se(streq(strv_env_get_n(env, "PATH", 4, 0), "unset"));
        assert_se(streq(strv_env_get_n(env, "PATH__", 4, REPLACE_ENV_USE_ENVIRONMENT), "unset"));
        assert_se(streq(strv_env_get_n(env, "PATH", 4, REPLACE_ENV_USE_ENVIRONMENT), "unset"));

        env[3] = NULL; /* kill our $PATH */

        assert_se(!strv_env_get_n(env, "PATH__", 4, 0));
        assert_se(!strv_env_get_n(env, "PATH", 4, 0));
        assert_se(streq_ptr(strv_env_get_n(env, "PATH__", 4, REPLACE_ENV_USE_ENVIRONMENT),
                            getenv("PATH")));
        assert_se(streq_ptr(strv_env_get_n(env, "PATH", 4, REPLACE_ENV_USE_ENVIRONMENT),
                            getenv("PATH")));
}