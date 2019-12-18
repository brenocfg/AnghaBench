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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  test_dns_label_escape () ; 
 int /*<<< orphan*/  test_dns_label_unescape () ; 
 int /*<<< orphan*/  test_dns_label_unescape_suffix () ; 
 int /*<<< orphan*/  test_dns_name_apply_idna () ; 
 int /*<<< orphan*/  test_dns_name_between () ; 
 int /*<<< orphan*/  test_dns_name_change_suffix () ; 
 int /*<<< orphan*/  test_dns_name_common_suffix () ; 
 int /*<<< orphan*/  test_dns_name_compare_func () ; 
 int /*<<< orphan*/  test_dns_name_concat () ; 
 int /*<<< orphan*/  test_dns_name_count_labels () ; 
 int /*<<< orphan*/  test_dns_name_endswith () ; 
 int /*<<< orphan*/  test_dns_name_equal () ; 
 int /*<<< orphan*/  test_dns_name_equal_skip () ; 
 int /*<<< orphan*/  test_dns_name_is_root () ; 
 int /*<<< orphan*/  test_dns_name_is_single_label () ; 
 int /*<<< orphan*/  test_dns_name_is_valid () ; 
 int /*<<< orphan*/  test_dns_name_is_valid_or_address () ; 
 int /*<<< orphan*/  test_dns_name_normalize () ; 
 int /*<<< orphan*/  test_dns_name_reverse () ; 
 int /*<<< orphan*/  test_dns_name_startswith () ; 
 int /*<<< orphan*/  test_dns_name_suffix () ; 
 int /*<<< orphan*/  test_dns_name_to_wire_format () ; 
 int /*<<< orphan*/  test_dns_service_join () ; 
 int /*<<< orphan*/  test_dns_service_name_is_valid () ; 
 int /*<<< orphan*/  test_dns_service_split () ; 
 int /*<<< orphan*/  test_dns_srv_type_is_valid () ; 
 int /*<<< orphan*/  test_dnssd_srv_type_is_valid () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_dns_label_unescape();
        test_dns_label_unescape_suffix();
        test_dns_label_escape();
        test_dns_name_normalize();
        test_dns_name_equal();
        test_dns_name_endswith();
        test_dns_name_startswith();
        test_dns_name_between();
        test_dns_name_is_root();
        test_dns_name_is_single_label();
        test_dns_name_reverse();
        test_dns_name_concat();
        test_dns_name_is_valid();
        test_dns_name_to_wire_format();
        test_dns_service_name_is_valid();
        test_dns_srv_type_is_valid();
        test_dnssd_srv_type_is_valid();
        test_dns_service_join();
        test_dns_service_split();
        test_dns_name_change_suffix();
        test_dns_name_suffix();
        test_dns_name_count_labels();
        test_dns_name_equal_skip();
        test_dns_name_compare_func();
        test_dns_name_common_suffix();
        test_dns_name_apply_idna();
        test_dns_name_is_valid_or_address();

        return 0;
}