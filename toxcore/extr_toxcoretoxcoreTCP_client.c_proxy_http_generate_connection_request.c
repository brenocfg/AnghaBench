#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ip ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {int last_packet_length; scalar_t__ last_packet_sent; scalar_t__ last_packet; TYPE_1__ ip_port; } ;
typedef  TYPE_2__ TCP_Client_Connection ;

/* Variables and functions */
 int INET6_ADDRSTRLEN ; 
 int const MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  ip_parse_addr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int const,char*,char*,char*,int /*<<< orphan*/  const,char*,char*,int /*<<< orphan*/  const,char*) ; 

__attribute__((used)) static int proxy_http_generate_connection_request(TCP_Client_Connection *TCP_conn)
{
    char one[] = "CONNECT ";
    char two[] = " HTTP/1.1\nHost: ";
    char three[] = "\r\n\r\n";

    char ip[INET6_ADDRSTRLEN];

    if (!ip_parse_addr(&TCP_conn->ip_port.ip, ip, sizeof(ip))) {
        return 0;
    }

    const uint16_t port = ntohs(TCP_conn->ip_port.port);
    const int written = snprintf((char *)TCP_conn->last_packet, MAX_PACKET_SIZE, "%s%s:%hu%s%s:%hu%s", one, ip, port, two,
                                 ip, port, three);

    if (written < 0 || MAX_PACKET_SIZE < written) {
        return 0;
    }

    TCP_conn->last_packet_length = written;
    TCP_conn->last_packet_sent = 0;

    return 1;
}