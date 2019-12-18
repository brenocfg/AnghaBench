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
 int EINVAL ; 
 unsigned int ELEMENTSOF (char**) ; 
 int af_from_name (char*) ; 
 int af_max () ; 
 char** af_names ; 
 int /*<<< orphan*/ * af_to_name (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int streq (int /*<<< orphan*/ *,char*) ; 

int main(int argc, const char *argv[]) {

        unsigned i;

        for (i = 0; i < ELEMENTSOF(af_names); i++) {
                if (af_names[i]) {
                        assert_se(streq(af_to_name(i), af_names[i]));
                        assert_se(af_from_name(af_names[i]) == (int) i);
                }
        }

        assert_se(af_to_name(af_max()) == NULL);
        assert_se(af_to_name(-1) == NULL);
        assert_se(af_from_name("huddlduddl") == -EINVAL);
        assert_se(af_from_name("") == -EINVAL);

        return 0;
}