#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {size_t num_listening_socks; int /*<<< orphan*/  accepted_key_list; int /*<<< orphan*/  secret_key; int /*<<< orphan*/  public_key; int /*<<< orphan*/ * onion; struct TYPE_8__* socks_listening; } ;
typedef  TYPE_1__ sock_t ;
typedef  TYPE_1__ TCP_Server ;
typedef  int /*<<< orphan*/  Onion ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  bs_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  crypto_scalarmult_curve25519_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_onion_recv_1 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ networking_at_startup () ; 
 TYPE_1__ new_listening_TCP_socket (scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  set_callback_handle_recv_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ sock_valid (TYPE_1__) ; 

TCP_Server *new_TCP_server(uint8_t ipv6_enabled, uint16_t num_sockets, const uint16_t *ports, const uint8_t *secret_key,
                           Onion *onion)
{
    if (num_sockets == 0 || ports == NULL)
        return NULL;

    if (networking_at_startup() != 0) {
        return NULL;
    }

    TCP_Server *temp = calloc(1, sizeof(TCP_Server));

    if (temp == NULL)
        return NULL;

    temp->socks_listening = calloc(num_sockets, sizeof(sock_t));

    if (temp->socks_listening == NULL) {
        free(temp);
        return NULL;
    }

#ifdef TCP_SERVER_USE_EPOLL
    temp->efd = epoll_create(8);

    if (temp->efd == -1) {
        free(temp->socks_listening);
        free(temp);
        return NULL;
    }

#endif

    uint8_t family;

    if (ipv6_enabled) {
        family = AF_INET6;
    } else {
        family = AF_INET;
    }

    uint32_t i;
#ifdef TCP_SERVER_USE_EPOLL
    struct epoll_event ev;
#endif

    for (i = 0; i < num_sockets; ++i) {
        sock_t sock = new_listening_TCP_socket(family, ports[i]);

        if (sock_valid(sock)) {
#ifdef TCP_SERVER_USE_EPOLL
            ev.events = EPOLLIN | EPOLLET;
            ev.data.u64 = sock | ((uint64_t)TCP_SOCKET_LISTENING << 32);

            if (epoll_ctl(temp->efd, EPOLL_CTL_ADD, sock, &ev) == -1) {
                continue;
            }

#endif

            temp->socks_listening[temp->num_listening_socks] = sock;
            ++temp->num_listening_socks;
        }
    }

    if (temp->num_listening_socks == 0) {
        free(temp->socks_listening);
        free(temp);
        return NULL;
    }

    if (onion) {
        temp->onion = onion;
        set_callback_handle_recv_1(onion, &handle_onion_recv_1, temp);
    }

    memcpy(temp->secret_key, secret_key, crypto_box_SECRETKEYBYTES);
    crypto_scalarmult_curve25519_base(temp->public_key, temp->secret_key);

    bs_list_init(&temp->accepted_key_list, crypto_box_PUBLICKEYBYTES, 8);

    return temp;
}