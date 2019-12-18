#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_13__ {int /*<<< orphan*/  key; } ;
struct TYPE_10__ {TYPE_5__ node; TYPE_4__* connection; } ;
typedef  TYPE_2__ ngx_udp_connection_t ;
struct TYPE_11__ {int /*<<< orphan*/  handler; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_pool_cleanup_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {TYPE_2__* udp; TYPE_1__* listening; int /*<<< orphan*/  pool; int /*<<< orphan*/  local_socklen; scalar_t__ local_sockaddr; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_9__ {int /*<<< orphan*/  rbtree; scalar_t__ wildcard; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_crc32_final (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_crc32_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_crc32_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_delete_udp_connection ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rbtree_insert (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static ngx_int_t
ngx_insert_udp_connection(ngx_connection_t *c)
{
    uint32_t               hash;
    ngx_pool_cleanup_t    *cln;
    ngx_udp_connection_t  *udp;

    if (c->udp) {
        return NGX_OK;
    }

    udp = ngx_pcalloc(c->pool, sizeof(ngx_udp_connection_t));
    if (udp == NULL) {
        return NGX_ERROR;
    }

    udp->connection = c;

    ngx_crc32_init(hash);
    ngx_crc32_update(&hash, (u_char *) c->sockaddr, c->socklen);

    if (c->listening->wildcard) {
        ngx_crc32_update(&hash, (u_char *) c->local_sockaddr, c->local_socklen);
    }

    ngx_crc32_final(hash);

    udp->node.key = hash;

    cln = ngx_pool_cleanup_add(c->pool, 0);
    if (cln == NULL) {
        return NGX_ERROR;
    }

    cln->data = c;
    cln->handler = ngx_delete_udp_connection;

    ngx_rbtree_insert(&c->listening->rbtree, &udp->node);

    c->udp = udp;

    return NGX_OK;
}