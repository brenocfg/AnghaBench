#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  self_secret_key; } ;
struct TYPE_12__ {scalar_t__ tcp_server_port; int /*<<< orphan*/  ipv6enabled; int /*<<< orphan*/  proxy_info; int /*<<< orphan*/ * port_range; scalar_t__ udp_disabled; } ;
struct TYPE_13__ {int /*<<< orphan*/  fr; int /*<<< orphan*/  fr_c; TYPE_1__ options; int /*<<< orphan*/ * net; TYPE_4__* dht; int /*<<< orphan*/ * net_crypto; scalar_t__ onion_c; scalar_t__ onion_a; scalar_t__ onion; int /*<<< orphan*/ * tcp_server; } ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  TYPE_1__ Messenger_Options ;
typedef  TYPE_2__ Messenger ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 unsigned int MESSENGER_ERROR_NONE ; 
 unsigned int MESSENGER_ERROR_OTHER ; 
 unsigned int MESSENGER_ERROR_PORT ; 
 unsigned int MESSENGER_ERROR_TCP_SERVER ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  friend_already_added ; 
 int /*<<< orphan*/  friendreq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_DHT (TYPE_4__*) ; 
 int /*<<< orphan*/  kill_friend_connections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_net_crypto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_networking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_onion (scalar_t__) ; 
 int /*<<< orphan*/  kill_onion_announce (scalar_t__) ; 
 int /*<<< orphan*/  kill_onion_client (scalar_t__) ; 
 TYPE_4__* new_DHT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_TCP_server (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  new_friend_connections (scalar_t__) ; 
 int /*<<< orphan*/ * new_net_crypto (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_networking_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ new_onion (TYPE_4__*) ; 
 scalar_t__ new_onion_announce (TYPE_4__*) ; 
 scalar_t__ new_onion_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_int () ; 
 int /*<<< orphan*/  set_filter_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  set_nospam (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Messenger *new_messenger(Messenger_Options *options, unsigned int *error)
{
    Messenger *m = calloc(1, sizeof(Messenger));

    if (error)
        *error = MESSENGER_ERROR_OTHER;

    if ( ! m )
        return NULL;

    unsigned int net_err = 0;

    if (options->udp_disabled) {
        /* this is the easiest way to completely disable UDP without changing too much code. */
        m->net = calloc(1, sizeof(Networking_Core));
    } else {
        IP ip;
        ip_init(&ip, options->ipv6enabled);
        m->net = new_networking_ex(ip, options->port_range[0], options->port_range[1], &net_err);
    }

    if (m->net == NULL) {
        free(m);

        if (error && net_err == 1) {
            *error = MESSENGER_ERROR_PORT;
        }

        return NULL;
    }

    m->dht = new_DHT(m->net);

    if (m->dht == NULL) {
        kill_networking(m->net);
        free(m);
        return NULL;
    }

    m->net_crypto = new_net_crypto(m->dht, &options->proxy_info);

    if (m->net_crypto == NULL) {
        kill_networking(m->net);
        kill_DHT(m->dht);
        free(m);
        return NULL;
    }

    m->onion = new_onion(m->dht);
    m->onion_a = new_onion_announce(m->dht);
    m->onion_c =  new_onion_client(m->net_crypto);
    m->fr_c = new_friend_connections(m->onion_c);

    if (!(m->onion && m->onion_a && m->onion_c)) {
        kill_friend_connections(m->fr_c);
        kill_onion(m->onion);
        kill_onion_announce(m->onion_a);
        kill_onion_client(m->onion_c);
        kill_net_crypto(m->net_crypto);
        kill_DHT(m->dht);
        kill_networking(m->net);
        free(m);
        return NULL;
    }

    if (options->tcp_server_port) {
        m->tcp_server = new_TCP_server(options->ipv6enabled, 1, &options->tcp_server_port, m->dht->self_secret_key, m->onion);

        if (m->tcp_server == NULL) {
            kill_friend_connections(m->fr_c);
            kill_onion(m->onion);
            kill_onion_announce(m->onion_a);
            kill_onion_client(m->onion_c);
            kill_net_crypto(m->net_crypto);
            kill_DHT(m->dht);
            kill_networking(m->net);
            free(m);

            if (error)
                *error = MESSENGER_ERROR_TCP_SERVER;

            return NULL;
        }
    }

    m->options = *options;
    friendreq_init(&(m->fr), m->fr_c);
    set_nospam(&(m->fr), random_int());
    set_filter_function(&(m->fr), &friend_already_added, m);

    if (error)
        *error = MESSENGER_ERROR_NONE;

    return m;
}