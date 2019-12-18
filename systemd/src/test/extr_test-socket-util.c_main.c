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
 int /*<<< orphan*/  test_flush_accept () ; 
 int /*<<< orphan*/  test_getpeercred_getpeergroups () ; 
 int /*<<< orphan*/  test_ifname_valid () ; 
 int /*<<< orphan*/  test_in_addr_ifindex_from_string_auto () ; 
 int /*<<< orphan*/  test_in_addr_ifindex_to_string () ; 
 int /*<<< orphan*/  test_in_addr_is_multicast () ; 
 int /*<<< orphan*/  test_in_addr_is_null () ; 
 int /*<<< orphan*/  test_in_addr_prefix_intersect () ; 
 int /*<<< orphan*/  test_in_addr_prefix_next () ; 
 int /*<<< orphan*/  test_in_addr_to_string () ; 
 int /*<<< orphan*/  test_passfd_contents_read () ; 
 int /*<<< orphan*/  test_passfd_read () ; 
 int /*<<< orphan*/  test_receive_nopassfd () ; 
 int /*<<< orphan*/  test_send_emptydata () ; 
 int /*<<< orphan*/  test_send_nodata_nofd () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_sockaddr_equal () ; 
 int /*<<< orphan*/  test_sockaddr_un_len () ; 
 int /*<<< orphan*/  test_socket_address_equal () ; 
 int /*<<< orphan*/  test_socket_address_get_path () ; 
 int /*<<< orphan*/  test_socket_address_is () ; 
 int /*<<< orphan*/  test_socket_address_is_netlink () ; 
 int /*<<< orphan*/  test_socket_address_parse () ; 
 int /*<<< orphan*/  test_socket_address_parse_netlink () ; 
 int /*<<< orphan*/  test_socket_print_unix () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_ifname_valid();

        test_socket_address_parse();
        test_socket_print_unix();
        test_socket_address_parse_netlink();
        test_socket_address_equal();
        test_socket_address_get_path();
        test_socket_address_is();
        test_socket_address_is_netlink();

        test_in_addr_is_null();
        test_in_addr_prefix_intersect();
        test_in_addr_prefix_next();
        test_in_addr_to_string();
        test_in_addr_ifindex_to_string();
        test_in_addr_ifindex_from_string_auto();

        test_sockaddr_equal();

        test_sockaddr_un_len();

        test_in_addr_is_multicast();

        test_getpeercred_getpeergroups();

        test_passfd_read();
        test_passfd_contents_read();
        test_receive_nopassfd();
        test_send_nodata_nofd();
        test_send_emptydata();
        test_flush_accept();

        return 0;
}