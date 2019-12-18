#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sock_t ;
struct TYPE_17__ {scalar_t__ family; } ;
struct TYPE_22__ {TYPE_1__ ip; } ;
struct TYPE_18__ {scalar_t__ family; } ;
struct TYPE_19__ {TYPE_2__ ip; } ;
struct TYPE_20__ {int proxy_type; TYPE_3__ ip_port; } ;
struct TYPE_21__ {scalar_t__ kill_at; int /*<<< orphan*/  status; TYPE_4__ proxy_info; TYPE_6__ ip_port; int /*<<< orphan*/  shared_key; int /*<<< orphan*/  public_key; int /*<<< orphan*/  self_public_key; int /*<<< orphan*/  sock; } ;
typedef  TYPE_4__ TCP_Proxy_Info ;
typedef  TYPE_5__ TCP_Client_Connection ;
typedef  TYPE_6__ IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_CLIENT_CONNECTING ; 
 int /*<<< orphan*/  TCP_CLIENT_PROXY_HTTP_CONNECTING ; 
 int /*<<< orphan*/  TCP_CLIENT_PROXY_SOCKS5_CONNECTING ; 
 scalar_t__ TCP_CONNECTION_TIMEOUT ; 
#define  TCP_PROXY_HTTP 130 
#define  TCP_PROXY_NONE 129 
#define  TCP_PROXY_SOCKS5 128 
 TYPE_5__* calloc (int,int) ; 
 scalar_t__ connect_sock_to (int /*<<< orphan*/ ,TYPE_6__,TYPE_4__*) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  encrypt_precompute (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int generate_handshake (TYPE_5__*) ; 
 int /*<<< orphan*/  kill_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ networking_at_startup () ; 
 int /*<<< orphan*/  proxy_http_generate_connection_request (TYPE_5__*) ; 
 int /*<<< orphan*/  proxy_socks5_generate_handshake (TYPE_5__*) ; 
 scalar_t__ set_socket_nonblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_socket_nosigpipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unix_time () ; 

TCP_Client_Connection *new_TCP_connection(IP_Port ip_port, const uint8_t *public_key, const uint8_t *self_public_key,
        const uint8_t *self_secret_key, TCP_Proxy_Info *proxy_info)
{
    if (networking_at_startup() != 0) {
        return NULL;
    }

    if (ip_port.ip.family != AF_INET && ip_port.ip.family != AF_INET6)
        return NULL;

    uint8_t family = ip_port.ip.family;

    TCP_Proxy_Info default_proxyinfo;

    if (proxy_info == NULL) {
        default_proxyinfo.proxy_type = TCP_PROXY_NONE;
        proxy_info = &default_proxyinfo;
    }

    if (proxy_info->proxy_type != TCP_PROXY_NONE) {
        family = proxy_info->ip_port.ip.family;
    }

    sock_t sock = socket(family, SOCK_STREAM, IPPROTO_TCP);

    if (!sock_valid(sock)) {
        return NULL;
    }

    if (!set_socket_nosigpipe(sock)) {
        kill_sock(sock);
        return 0;
    }

    if (!(set_socket_nonblock(sock) && connect_sock_to(sock, ip_port, proxy_info))) {
        kill_sock(sock);
        return NULL;
    }

    TCP_Client_Connection *temp = calloc(sizeof(TCP_Client_Connection), 1);

    if (temp == NULL) {
        kill_sock(sock);
        return NULL;
    }

    temp->sock = sock;
    memcpy(temp->public_key, public_key, crypto_box_PUBLICKEYBYTES);
    memcpy(temp->self_public_key, self_public_key, crypto_box_PUBLICKEYBYTES);
    encrypt_precompute(temp->public_key, self_secret_key, temp->shared_key);
    temp->ip_port = ip_port;
    temp->proxy_info = *proxy_info;

    switch (proxy_info->proxy_type) {
        case TCP_PROXY_HTTP:
            temp->status = TCP_CLIENT_PROXY_HTTP_CONNECTING;
            proxy_http_generate_connection_request(temp);
            break;

        case TCP_PROXY_SOCKS5:
            temp->status = TCP_CLIENT_PROXY_SOCKS5_CONNECTING;
            proxy_socks5_generate_handshake(temp);
            break;

        case TCP_PROXY_NONE:
            temp->status = TCP_CLIENT_CONNECTING;

            if (generate_handshake(temp) == -1) {
                kill_sock(sock);
                free(temp);
                return NULL;
            }

            break;
    }

    temp->kill_at = unix_time() + TCP_CONNECTION_TIMEOUT;

    return temp;
}