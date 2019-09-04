#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  public_key; } ;
struct TYPE_13__ {int /*<<< orphan*/  uint32; } ;
struct TYPE_14__ {TYPE_2__ ip4; int /*<<< orphan*/  family; } ;
struct TYPE_17__ {TYPE_3__ ip; int /*<<< orphan*/  port; } ;
struct TYPE_15__ {int /*<<< orphan*/  udp_disabled; int /*<<< orphan*/  tcp_server_port; } ;
struct TYPE_16__ {int has_added_relays; int /*<<< orphan*/  fr_c; int /*<<< orphan*/  onion_c; int /*<<< orphan*/  net_crypto; TYPE_9__* tcp_server; int /*<<< orphan*/  dht; int /*<<< orphan*/  net; TYPE_4__ options; TYPE_1__* loaded_relays; } ;
struct TYPE_12__ {int /*<<< orphan*/  public_key; TYPE_6__ ip_port; } ;
typedef  TYPE_5__ Messenger ;
typedef  TYPE_6__ IP_Port ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int NUM_SAVED_TCP_RELAYS ; 
 int /*<<< orphan*/  add_tcp_relay (int /*<<< orphan*/ ,TYPE_6__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_status_cb (TYPE_5__*) ; 
 int /*<<< orphan*/  do_DHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_TCP_server (TYPE_9__*) ; 
 int /*<<< orphan*/  do_friend_connections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_friends (TYPE_5__*) ; 
 int /*<<< orphan*/  do_net_crypto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_onion_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  networking_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time_update () ; 

void do_messenger(Messenger *m)
{
    // Add the TCP relays, but only if this is the first time calling do_messenger
    if (m->has_added_relays == 0) {
        m->has_added_relays = 1;

        int i;

        for (i = 0; i < NUM_SAVED_TCP_RELAYS; ++i) {
            add_tcp_relay(m->net_crypto, m->loaded_relays[i].ip_port, m->loaded_relays[i].public_key);
        }

        if (m->tcp_server) {
            /* Add self tcp server. */
            IP_Port local_ip_port;
            local_ip_port.port = m->options.tcp_server_port;
            local_ip_port.ip.family = AF_INET;
            local_ip_port.ip.ip4.uint32 = INADDR_LOOPBACK;
            add_tcp_relay(m->net_crypto, local_ip_port, m->tcp_server->public_key);
        }
    }

    unix_time_update();

    if (!m->options.udp_disabled) {
        networking_poll(m->net);
        do_DHT(m->dht);
    }

    if (m->tcp_server) {
        do_TCP_server(m->tcp_server);
    }

    do_net_crypto(m->net_crypto);
    do_onion_client(m->onion_c);
    do_friend_connections(m->fr_c);
    do_friends(m);
    connection_status_cb(m);

#ifdef TOX_LOGGER

    if (unix_time() > lastdump + DUMPING_CLIENTS_FRIENDS_EVERY_N_SECONDS) {

#ifdef ENABLE_ASSOC_DHT
        Assoc_status(m->dht->assoc);
#endif

        lastdump = unix_time();
        uint32_t client, last_pinged;

        for (client = 0; client < LCLIENT_LIST; client++) {
            Client_data *cptr = &m->dht->close_clientlist[client];
            IPPTsPng *assoc = NULL;
            uint32_t a;

            for (a = 0, assoc = &cptr->assoc4; a < 2; a++, assoc = &cptr->assoc6)
                if (ip_isset(&assoc->ip_port.ip)) {
                    last_pinged = lastdump - assoc->last_pinged;

                    if (last_pinged > 999)
                        last_pinged = 999;

                    LOGGER_TRACE("C[%2u] %s:%u [%3u] %s",
                                 client, ip_ntoa(&assoc->ip_port.ip), ntohs(assoc->ip_port.port),
                                 last_pinged, ID2String(cptr->public_key));
                }
        }


        uint32_t friend, dhtfriend;

        /* dht contains additional "friends" (requests) */
        uint32_t num_dhtfriends = m->dht->num_friends;
        int32_t m2dht[num_dhtfriends];
        int32_t dht2m[num_dhtfriends];

        for (friend = 0; friend < num_dhtfriends; friend++) {
            m2dht[friend] = -1;
            dht2m[friend] = -1;

            if (friend >= m->numfriends)
                continue;

            for (dhtfriend = 0; dhtfriend < m->dht->num_friends; dhtfriend++)
                if (id_equal(m->friendlist[friend].real_pk, m->dht->friends_list[dhtfriend].public_key)) {
                    m2dht[friend] = dhtfriend;
                    break;
                }
        }

        for (friend = 0; friend < num_dhtfriends; friend++)
            if (m2dht[friend] >= 0)
                dht2m[m2dht[friend]] = friend;

        if (m->numfriends != m->dht->num_friends) {
            LOGGER_TRACE("Friend num in DHT %u != friend num in msger %u\n", m->dht->num_friends, m->numfriends);
        }

        Friend *msgfptr;
        DHT_Friend *dhtfptr;

        for (friend = 0; friend < num_dhtfriends; friend++) {
            if (dht2m[friend] >= 0)
                msgfptr = &m->friendlist[dht2m[friend]];
            else
                msgfptr = NULL;

            dhtfptr = &m->dht->friends_list[friend];

            if (msgfptr) {
                LOGGER_TRACE("F[%2u:%2u] <%s> %s",
                             dht2m[friend], friend, msgfptr->name,
                             ID2String(msgfptr->real_pk));
            } else {
                LOGGER_TRACE("F[--:%2u] %s", friend, ID2String(dhtfptr->public_key));
            }

            for (client = 0; client < MAX_FRIEND_CLIENTS; client++) {
                Client_data *cptr = &dhtfptr->client_list[client];
                IPPTsPng *assoc = NULL;
                uint32_t a;

                for (a = 0, assoc = &cptr->assoc4; a < 2; a++, assoc = &cptr->assoc6)
                    if (ip_isset(&assoc->ip_port.ip)) {
                        last_pinged = lastdump - assoc->last_pinged;

                        if (last_pinged > 999)
                            last_pinged = 999;

                        LOGGER_TRACE("F[%2u] => C[%2u] %s:%u [%3u] %s",
                                     friend, client, ip_ntoa(&assoc->ip_port.ip),
                                     ntohs(assoc->ip_port.port), last_pinged,
                                     ID2String(cptr->public_key));
                    }
            }
        }
    }

#endif /* TOX_LOGGER */
}