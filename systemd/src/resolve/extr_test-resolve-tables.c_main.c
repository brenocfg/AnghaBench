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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNSSEC_RESULT ; 
 int /*<<< orphan*/  DNSSEC_VERDICT ; 
 int /*<<< orphan*/  DNS_PROTOCOL ; 
 int /*<<< orphan*/  DNS_RCODE ; 
 int /*<<< orphan*/  DNS_TYPE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ _DNS_CLASS_MAX ; 
 scalar_t__ _DNS_CLASS_STRING_MAX ; 
 scalar_t__ _DNS_TYPE_MAX ; 
 scalar_t__ _DNS_TYPE_STRING_MAX ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ dns_class_is_pseudo (scalar_t__) ; 
 scalar_t__ dns_class_is_valid_rr (scalar_t__) ; 
 char* dns_class_to_string (scalar_t__) ; 
 int /*<<< orphan*/  dns_protocol ; 
 int /*<<< orphan*/  dns_rcode ; 
 int /*<<< orphan*/  dns_type ; 
 scalar_t__ dns_type_apex_only (scalar_t__) ; 
 scalar_t__ dns_type_is_dnssec (scalar_t__) ; 
 scalar_t__ dns_type_is_obsolete (scalar_t__) ; 
 scalar_t__ dns_type_is_pseudo (scalar_t__) ; 
 scalar_t__ dns_type_is_valid_query (scalar_t__) ; 
 scalar_t__ dns_type_is_valid_rr (scalar_t__) ; 
 scalar_t__ dns_type_may_redirect (scalar_t__) ; 
 scalar_t__ dns_type_may_wildcard (scalar_t__) ; 
 scalar_t__ dns_type_needs_authentication (scalar_t__) ; 
 char* dns_type_to_string (scalar_t__) ; 
 int /*<<< orphan*/  dnssec_result ; 
 int /*<<< orphan*/  dnssec_verdict ; 
 int /*<<< orphan*/  log_info (char*,...) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  test_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_table_sparse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
        uint16_t i;

        test_table(dns_protocol, DNS_PROTOCOL);
        test_table(dnssec_result, DNSSEC_RESULT);
        test_table(dnssec_verdict, DNSSEC_VERDICT);

        test_table_sparse(dns_rcode, DNS_RCODE);
        test_table_sparse(dns_type, DNS_TYPE);

        log_info("/* DNS_TYPE */");
        for (i = 0; i < _DNS_TYPE_MAX; i++) {
                const char *s;

                s = dns_type_to_string(i);
                assert_se(s == NULL || strlen(s) < _DNS_TYPE_STRING_MAX);

                if (s)
                        log_info("%-*s %s%s%s%s%s%s%s%s%s",
                                 (int) _DNS_TYPE_STRING_MAX - 1, s,
                                 dns_type_is_pseudo(i) ? "pseudo " : "",
                                 dns_type_is_valid_query(i) ? "valid_query " : "",
                                 dns_type_is_valid_rr(i) ? "is_valid_rr " : "",
                                 dns_type_may_redirect(i) ? "may_redirect " : "",
                                 dns_type_is_dnssec(i) ? "dnssec " : "",
                                 dns_type_is_obsolete(i) ? "obsolete " : "",
                                 dns_type_may_wildcard(i) ? "wildcard " : "",
                                 dns_type_apex_only(i) ? "apex_only " : "",
                                 dns_type_needs_authentication(i) ? "needs_authentication" : "");
        }

        log_info("/* DNS_CLASS */");
        for (i = 0; i < _DNS_CLASS_MAX; i++) {
                const char *s;

                s = dns_class_to_string(i);
                assert_se(s == NULL || strlen(s) < _DNS_CLASS_STRING_MAX);

                if (s)
                        log_info("%-*s %s%s",
                                 (int) _DNS_CLASS_STRING_MAX - 1, s,
                                 dns_class_is_pseudo(i) ? "is_pseudo " : "",
                                 dns_class_is_valid_rr(i) ? "is_valid_rr " : "");
        }

        return EXIT_SUCCESS;
}