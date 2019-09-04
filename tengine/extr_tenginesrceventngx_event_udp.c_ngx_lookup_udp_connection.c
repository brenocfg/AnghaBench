#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_9__ {TYPE_5__* connection; } ;
typedef  TYPE_2__ ngx_udp_connection_t ;
struct TYPE_10__ {scalar_t__ key; struct TYPE_10__* right; struct TYPE_10__* left; } ;
typedef  TYPE_3__ ngx_rbtree_node_t ;
struct TYPE_8__ {TYPE_3__* sentinel; TYPE_3__* root; } ;
struct TYPE_11__ {scalar_t__ wildcard; TYPE_1__ rbtree; } ;
typedef  TYPE_4__ ngx_listening_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/  local_socklen; int /*<<< orphan*/  local_sockaddr; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_5__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ ngx_cmp_sockaddr (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_crc32_final (scalar_t__) ; 
 int /*<<< orphan*/  ngx_crc32_init (scalar_t__) ; 
 int /*<<< orphan*/  ngx_crc32_update (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_connection_t *
ngx_lookup_udp_connection(ngx_listening_t *ls, struct sockaddr *sockaddr,
    socklen_t socklen, struct sockaddr *local_sockaddr, socklen_t local_socklen)
{
    uint32_t               hash;
    ngx_int_t              rc;
    ngx_connection_t      *c;
    ngx_rbtree_node_t     *node, *sentinel;
    ngx_udp_connection_t  *udp;

#if (NGX_HAVE_UNIX_DOMAIN)

    if (sockaddr->sa_family == AF_UNIX) {
        struct sockaddr_un *saun = (struct sockaddr_un *) sockaddr;

        if (socklen <= (socklen_t) offsetof(struct sockaddr_un, sun_path)
            || saun->sun_path[0] == '\0')
        {
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, ngx_cycle->log, 0,
                           "unbound unix socket");
            return NULL;
        }
    }

#endif

    node = ls->rbtree.root;
    sentinel = ls->rbtree.sentinel;

    ngx_crc32_init(hash);
    ngx_crc32_update(&hash, (u_char *) sockaddr, socklen);

    if (ls->wildcard) {
        ngx_crc32_update(&hash, (u_char *) local_sockaddr, local_socklen);
    }

    ngx_crc32_final(hash);

    while (node != sentinel) {

        if (hash < node->key) {
            node = node->left;
            continue;
        }

        if (hash > node->key) {
            node = node->right;
            continue;
        }

        /* hash == node->key */

        udp = (ngx_udp_connection_t *) node;

        c = udp->connection;

        rc = ngx_cmp_sockaddr(sockaddr, socklen,
                              c->sockaddr, c->socklen, 1);

        if (rc == 0 && ls->wildcard) {
            rc = ngx_cmp_sockaddr(local_sockaddr, local_socklen,
                                  c->local_sockaddr, c->local_socklen, 1);
        }

        if (rc == 0) {
            return c;
        }

        node = (rc < 0) ? node->left : node->right;
    }

    return NULL;
}