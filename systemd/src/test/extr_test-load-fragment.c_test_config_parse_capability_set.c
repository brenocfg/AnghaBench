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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int UINT64_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int cap_test_all (int) ; 
 int config_parse_capability_set (int /*<<< orphan*/ *,char*,int,char*,int,char*,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *) ; 
 int make_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_config_parse_capability_set(void) {
        /* int config_parse_capability_set(
                 const char *unit,
                 const char *filename,
                 unsigned line,
                 const char *section,
                 unsigned section_line,
                 const char *lvalue,
                 int ltype,
                 const char *rvalue,
                 void *data,
                 void *userdata) */
        int r;
        uint64_t capability_bounding_set = 0;

        r = config_parse_capability_set(NULL, "fake", 1, "section", 1,
                              "CapabilityBoundingSet", 0, "CAP_NET_RAW",
                              &capability_bounding_set, NULL);
        assert_se(r >= 0);
        assert_se(capability_bounding_set == make_cap(CAP_NET_RAW));

        r = config_parse_capability_set(NULL, "fake", 1, "section", 1,
                              "CapabilityBoundingSet", 0, "CAP_NET_ADMIN",
                              &capability_bounding_set, NULL);
        assert_se(r >= 0);
        assert_se(capability_bounding_set == (make_cap(CAP_NET_RAW) | make_cap(CAP_NET_ADMIN)));

        r = config_parse_capability_set(NULL, "fake", 1, "section", 1,
                              "CapabilityBoundingSet", 0, "~CAP_NET_ADMIN",
                              &capability_bounding_set, NULL);
        assert_se(r >= 0);
        assert_se(capability_bounding_set == make_cap(CAP_NET_RAW));

        r = config_parse_capability_set(NULL, "fake", 1, "section", 1,
                              "CapabilityBoundingSet", 0, "",
                              &capability_bounding_set, NULL);
        assert_se(r >= 0);
        assert_se(capability_bounding_set == UINT64_C(0));

        r = config_parse_capability_set(NULL, "fake", 1, "section", 1,
                              "CapabilityBoundingSet", 0, "~",
                              &capability_bounding_set, NULL);
        assert_se(r >= 0);
        assert_se(cap_test_all(capability_bounding_set));

        capability_bounding_set = 0;
        r = config_parse_capability_set(NULL, "fake", 1, "section", 1,
                              "CapabilityBoundingSet", 0, "  'CAP_NET_RAW' WAT_CAP??? CAP_NET_ADMIN CAP'_trailing_garbage",
                              &capability_bounding_set, NULL);
        assert_se(r >= 0);
        assert_se(capability_bounding_set == (make_cap(CAP_NET_RAW) | make_cap(CAP_NET_ADMIN)));
}