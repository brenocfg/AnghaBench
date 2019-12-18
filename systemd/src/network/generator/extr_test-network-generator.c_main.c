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
 int /*<<< orphan*/  test_link_one (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  test_netdev_one (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  test_network_one (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  test_network_two (char*,char*,char*,char*,char*,char*) ; 

int main(int argc, char *argv[]) {
        test_network_one("", "ip", "dhcp6",
                         "[Match]\n"
                         "Name=*\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=ipv6\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth0", "ip", "eth0:dhcp",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=ipv4\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth0", "ip", "eth0:dhcp:1530",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "MTUBytes=1530\n"
                         "\n[Network]\n"
                         "DHCP=ipv4\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth0", "ip", "eth0:dhcp:1530:00:11:22:33:44:55",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "MACAddress=00:11:22:33:44:55\n"
                         "MTUBytes=1530\n"
                         "\n[Network]\n"
                         "DHCP=ipv4\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth0", "ip", "192.168.0.10::192.168.0.1:255.255.255.0:hogehoge:eth0:on",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_one("eth0", "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_one("eth0", "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:1530",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "MTUBytes=1530\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_one("eth0", "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:1530:00:11:22:33:44:55",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "MACAddress=00:11:22:33:44:55\n"
                         "MTUBytes=1530\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_one("eth0", "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:10.10.10.10",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.10.10.10\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_one("eth0", "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:10.10.10.10:10.10.10.11",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.10.10.10\n"
                         "DNS=10.10.10.11\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_one("eth0", "ip", "[2001:1234:56:8f63::10]::[2001:1234:56:8f63::1]:64:hogehoge:eth0:on",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=2001:1234:56:8f63::10/64\n"
                         "\n[Route]\n"
                         "Gateway=2001:1234:56:8f63::1\n"
                         );

        test_network_one("eth0", "ip", "[2001:1234:56:8f63::10]:[2001:1234:56:8f63::2]:[2001:1234:56:8f63::1]:64:hogehoge:eth0:on",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=2001:1234:56:8f63::10/64\n"
                         "Peer=2001:1234:56:8f63::2\n"
                         "\n[Route]\n"
                         "Gateway=2001:1234:56:8f63::1\n"
                         );

        test_network_one("", "rd.route", "10.1.2.3/16:10.0.2.3",
                         "[Match]\n"
                         "Name=*\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "\n[DHCP]\n"
                         "\n[Route]\n"
                         "Destination=10.1.2.3/16\n"
                         "Gateway=10.0.2.3\n"
                         );

        test_network_one("eth0", "rd.route", "10.1.2.3/16:10.0.2.3:eth0",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "\n[DHCP]\n"
                         "\n[Route]\n"
                         "Destination=10.1.2.3/16\n"
                         "Gateway=10.0.2.3\n"
                         );

        test_network_one("", "nameserver", "10.1.2.3",
                         "[Match]\n"
                         "Name=*\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DNS=10.1.2.3\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("", "rd.peerdns", "0",
                         "[Match]\n"
                         "Name=*\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "\n[DHCP]\n"
                         "UseDNS=no\n"
                         );

        test_network_one("", "rd.peerdns", "1",
                         "[Match]\n"
                         "Name=*\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "\n[DHCP]\n"
                         "UseDNS=yes\n"
                         );

        test_network_one("eth0", "vlan", "vlan99:eth0",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "VLAN=vlan99\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth0", "bridge", "bridge99:eth0,eth1",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "Bridge=bridge99\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth1", "bridge", "bridge99:eth0,eth1",
                         "[Match]\n"
                         "Name=eth1\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "Bridge=bridge99\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth0", "bond", "bond99:eth0,eth1",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "Bond=bond99\n"
                         "\n[DHCP]\n"
                         );

        test_network_one("eth1", "bond", "bond99:eth0,eth1::1530",
                         "[Match]\n"
                         "Name=eth1\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "Bond=bond99\n"
                         "\n[DHCP]\n"
                         );

        test_netdev_one("bond99", "bond", "bond99:eth0,eth1::1530",
                        "[NetDev]\n"
                        "Kind=bond\n"
                        "Name=bond99\n"
                        "MTUBytes=1530\n"
                        );

        test_link_one("hogehoge", "ifname", "hogehoge:00:11:22:33:44:55",
                      "[Match]\n"
                      "MACAddress=00:11:22:33:44:55\n"
                      "\n[Link]\n"
                      "Name=hogehoge\n"
                      );

        test_network_two("eth0",
                         "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:10.10.10.10:10.10.10.11",
                         "rd.route", "10.1.2.3/16:10.0.2.3",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.10.10.10\n"
                         "DNS=10.10.10.11\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Destination=10.1.2.3/16\n"
                         "Gateway=10.0.2.3\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_two("eth0",
                         "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on",
                         "nameserver", "10.1.2.3",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.1.2.3\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_two("eth0",
                         "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:10.10.10.10:10.10.10.11",
                         "nameserver", "10.1.2.3",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.10.10.10\n"
                         "DNS=10.10.10.11\n"
                         "DNS=10.1.2.3\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_two("eth0",
                         "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:10.10.10.10:10.10.10.11",
                         "rd.peerdns", "1",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.10.10.10\n"
                         "DNS=10.10.10.11\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "UseDNS=yes\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        test_network_two("eth0",
                         "ip", "192.168.0.10:192.168.0.2:192.168.0.1:255.255.255.0:hogehoge:eth0:on:10.10.10.10:10.10.10.11",
                         "bridge", "bridge99:eth0,eth1",
                         "[Match]\n"
                         "Name=eth0\n"
                         "\n[Link]\n"
                         "\n[Network]\n"
                         "DHCP=yes\n"
                         "DNS=10.10.10.10\n"
                         "DNS=10.10.10.11\n"
                         "Bridge=bridge99\n"
                         "\n[DHCP]\n"
                         "Hostname=hogehoge\n"
                         "\n[Address]\n"
                         "Address=192.168.0.10/24\n"
                         "Peer=192.168.0.2\n"
                         "\n[Route]\n"
                         "Gateway=192.168.0.1\n"
                         );

        return 0;
}