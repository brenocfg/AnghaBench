#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_6__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_7__ {int socklen; struct sockaddr* sockaddr; } ;
typedef  TYPE_1__ ngx_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  peer_addr_text; TYPE_1__ peer; } ;
typedef  TYPE_2__ ngx_http_tfs_peer_connection_t ;
struct TYPE_9__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  port; } ;
typedef  TYPE_3__ ngx_http_tfs_inet_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_6__) ; 
 struct sockaddr_in* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_peer_set_addr(ngx_pool_t *pool, ngx_http_tfs_peer_connection_t *p,
    ngx_http_tfs_inet_t *addr)
{
    struct sockaddr_in     *in;
    ngx_peer_connection_t  *peer;

    if (addr == NULL) {
        return NGX_ERROR;
    }

    in = ngx_pcalloc(pool, sizeof(struct sockaddr_in));
    if (in == NULL) {
        return NGX_ERROR;
    }

    in->sin_family = AF_INET;
    in->sin_port = htons(addr->port);
    in->sin_addr.s_addr = addr->ip;

    peer = &p->peer;
    peer->sockaddr = (struct sockaddr *) in;
    peer->socklen = sizeof(struct sockaddr_in);

    ngx_sprintf(p->peer_addr_text, "%s:%d",
                inet_ntoa(in->sin_addr),
                ntohs(in->sin_port));

    return NGX_OK;
}