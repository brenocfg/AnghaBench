#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_9__ {scalar_t__ family; } ;
struct TYPE_13__ {TYPE_1__ ip; } ;
struct TYPE_12__ {unsigned int tcp_relay_counter; TYPE_2__* tcp_relays; int /*<<< orphan*/  crypt_connection_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  net_crypto; } ;
struct TYPE_10__ {int /*<<< orphan*/  public_key; TYPE_8__ ip_port; } ;
typedef  TYPE_3__ Friend_Connections ;
typedef  TYPE_4__ Friend_Conn ;

/* Variables and functions */
 unsigned int FRIEND_MAX_STORED_TCP_RELAYS ; 
 scalar_t__ add_tcp_relay_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_conn (TYPE_3__*,int) ; 

__attribute__((used)) static void connect_to_saved_tcp_relays(Friend_Connections *fr_c, int friendcon_id, unsigned int number)
{
    Friend_Conn *friend_con = get_conn(fr_c, friendcon_id);

    if (!friend_con)
        return;

    unsigned int i;

    for (i = 0; (i < FRIEND_MAX_STORED_TCP_RELAYS) && (number != 0); ++i) {
        uint16_t index = (friend_con->tcp_relay_counter - (i + 1)) % FRIEND_MAX_STORED_TCP_RELAYS;

        if (friend_con->tcp_relays[index].ip_port.ip.family) {
            if (add_tcp_relay_peer(fr_c->net_crypto, friend_con->crypt_connection_id, friend_con->tcp_relays[index].ip_port,
                                   friend_con->tcp_relays[index].public_key) == 0) {
                --number;
            }
        }
    }
}