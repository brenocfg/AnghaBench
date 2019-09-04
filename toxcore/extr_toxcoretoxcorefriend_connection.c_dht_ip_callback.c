#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int crypt_connection_id; scalar_t__ hosting_tcp_relay; int /*<<< orphan*/  dht_temp_pk; int /*<<< orphan*/  dht_ip_port_lastrecv; int /*<<< orphan*/  dht_ip_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  net_crypto; } ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_1__ Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  friend_add_tcp_relay (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  friend_new_connection (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_conn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_direct_ip_port (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static void dht_ip_callback(void *object, int32_t number, IP_Port ip_port)
{
    Friend_Connections *fr_c = object;
    Friend_Conn *friend_con = get_conn(fr_c, number);

    if (!friend_con)
        return;

    if (friend_con->crypt_connection_id == -1) {
        friend_new_connection(fr_c, number);
    }

    set_direct_ip_port(fr_c->net_crypto, friend_con->crypt_connection_id, ip_port, 1);
    friend_con->dht_ip_port = ip_port;
    friend_con->dht_ip_port_lastrecv = unix_time();

    if (friend_con->hosting_tcp_relay) {
        friend_add_tcp_relay(fr_c, number, ip_port, friend_con->dht_temp_pk);
        friend_con->hosting_tcp_relay = 0;
    }
}