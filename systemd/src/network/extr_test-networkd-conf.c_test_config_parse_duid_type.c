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
typedef  int /*<<< orphan*/  usec_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUID_TYPE_EN ; 
 int /*<<< orphan*/  DUID_TYPE_LL ; 
 int /*<<< orphan*/  DUID_TYPE_LLT ; 
 int /*<<< orphan*/  DUID_TYPE_UUID ; 
 int /*<<< orphan*/  test_config_parse_duid_type_one (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_config_parse_duid_type(void) {
        test_config_parse_duid_type_one("", 0, 0, 0);
        test_config_parse_duid_type_one("link-layer-time", 0, DUID_TYPE_LLT, 0);
        test_config_parse_duid_type_one("link-layer-time:2000-01-01 00:00:00 UTC", 0, DUID_TYPE_LLT, (usec_t) 946684800000000);
        test_config_parse_duid_type_one("vendor", 0, DUID_TYPE_EN, 0);
        test_config_parse_duid_type_one("vendor:2000-01-01 00:00:00 UTC", 0, 0, 0);
        test_config_parse_duid_type_one("link-layer", 0, DUID_TYPE_LL, 0);
        test_config_parse_duid_type_one("link-layer:2000-01-01 00:00:00 UTC", 0, 0, 0);
        test_config_parse_duid_type_one("uuid", 0, DUID_TYPE_UUID, 0);
        test_config_parse_duid_type_one("uuid:2000-01-01 00:00:00 UTC", 0, 0, 0);
        test_config_parse_duid_type_one("foo", 0, 0, 0);
        test_config_parse_duid_type_one("foo:2000-01-01 00:00:00 UTC", 0, 0, 0);
}