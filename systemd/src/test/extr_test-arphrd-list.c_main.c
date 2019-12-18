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
 int ARPHRD_VOID ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int arphrd_from_name (char const*) ; 
 char* arphrd_to_name (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*,int,char const*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, const char *argv[]) {
        test_setup_logging(LOG_INFO);

        for (int i = 0; i <= ARPHRD_VOID + 1; i++) {
                const char *name;

                name = arphrd_to_name(i);
                if (name) {
                        log_info("%i: %s", i, name);

                        assert_se(arphrd_from_name(name) == i);
                }
        }

        assert_se(arphrd_to_name(ARPHRD_VOID + 1) == NULL);
        assert_se(arphrd_from_name("huddlduddl") == -EINVAL);
        assert_se(arphrd_from_name("") == -EINVAL);

        return 0;
}