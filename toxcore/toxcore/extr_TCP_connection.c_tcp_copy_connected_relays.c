#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_12__ {scalar_t__ family; } ;
struct TYPE_13__ {TYPE_2__ ip; } ;
struct TYPE_16__ {TYPE_3__ ip_port; int /*<<< orphan*/  public_key; } ;
struct TYPE_15__ {unsigned int tcp_connections_length; } ;
struct TYPE_14__ {scalar_t__ status; TYPE_1__* connection; } ;
struct TYPE_11__ {TYPE_3__ ip_port; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_4__ TCP_con ;
typedef  TYPE_5__ TCP_Connections ;
typedef  TYPE_6__ Node_format ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ TCP_CONN_CONNECTED ; 
 scalar_t__ TCP_INET ; 
 scalar_t__ TCP_INET6 ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 TYPE_4__* get_tcp_connection (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int rand () ; 

unsigned int tcp_copy_connected_relays(TCP_Connections *tcp_c, Node_format *tcp_relays, uint16_t max_num)
{
    unsigned int i, copied = 0, r = rand();

    for (i = 0; (i < tcp_c->tcp_connections_length) && (copied < max_num); ++i) {
        TCP_con *tcp_con = get_tcp_connection(tcp_c, (i + r) % tcp_c->tcp_connections_length);

        if (!tcp_con) {
            continue;
        }

        if (tcp_con->status == TCP_CONN_CONNECTED) {
            memcpy(tcp_relays[copied].public_key, tcp_con->connection->public_key, crypto_box_PUBLICKEYBYTES);
            tcp_relays[copied].ip_port = tcp_con->connection->ip_port;

            if (tcp_relays[copied].ip_port.ip.family == AF_INET) {
                tcp_relays[copied].ip_port.ip.family = TCP_INET;
            } else if (tcp_relays[copied].ip_port.ip.family == AF_INET6) {
                tcp_relays[copied].ip_port.ip.family = TCP_INET6;
            }

            ++copied;
        }
    }

    return copied;
}