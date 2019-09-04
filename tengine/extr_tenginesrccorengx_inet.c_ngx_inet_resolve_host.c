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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_11__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; void* sin_port; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/ ** h_addr_list; } ;
struct TYPE_16__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {char* err; size_t naddrs; TYPE_3__* addrs; TYPE_6__ host; int /*<<< orphan*/  port; } ;
typedef  TYPE_4__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_addr_t ;
typedef  void* in_port_t ;
typedef  scalar_t__ in_addr_t ;
struct TYPE_12__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int socklen; TYPE_2__ name; struct sockaddr* sockaddr; } ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 struct hostent* gethostbyname (char*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_cpystrn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_inet_addr (int /*<<< orphan*/ ,size_t) ; 
 void* ngx_pcalloc (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_sock_ntop (struct sockaddr*,int,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (void*) ; 

ngx_int_t
ngx_inet_resolve_host(ngx_pool_t *pool, ngx_url_t *u)
{
    u_char              *p, *host;
    size_t               len;
    in_port_t            port;
    in_addr_t            in_addr;
    ngx_uint_t           i;
    struct hostent      *h;
    struct sockaddr_in  *sin;
#if (T_NGX_DNS_RESOLVE_BACKUP)
    u_char              *ph;
    ngx_str_t            path;
#endif

    /* AF_INET only */

    port = htons(u->port);

    in_addr = ngx_inet_addr(u->host.data, u->host.len);

    if (in_addr == INADDR_NONE) {
        host = ngx_alloc(u->host.len + 1, pool->log);
        if (host == NULL) {
            return NGX_ERROR;
        }

        (void) ngx_cpystrn(host, u->host.data, u->host.len + 1);

        h = gethostbyname((char *) host);

#if (T_NGX_DNS_RESOLVE_BACKUP)
        ph = (u_char *) getenv(NGX_DNS_RESOLVE_BACKUP_PATH);
        if (h == NULL && ph != NULL) {
            path.data = ph;
            path.len = ngx_strlen(ph);
            if (ngx_resolve_using_local(pool, &u, path) == NGX_OK) {
                ngx_log_error(NGX_LOG_WARN, ngx_cycle->log, 0,
                              "dom %V using local dns cache successed",
                              &u->host);
                ngx_free(host);
                return NGX_OK;
            }
        }
#endif

        ngx_free(host);

        if (h == NULL || h->h_addr_list[0] == NULL) {
            u->err = "host not found";
            return NGX_ERROR;
        }

        for (i = 0; h->h_addr_list[i] != NULL; i++) { /* void */ }

        /* MP: ngx_shared_palloc() */

        u->addrs = ngx_pcalloc(pool, i * sizeof(ngx_addr_t));
        if (u->addrs == NULL) {
            return NGX_ERROR;
        }

        u->naddrs = i;

        for (i = 0; i < u->naddrs; i++) {

            sin = ngx_pcalloc(pool, sizeof(struct sockaddr_in));
            if (sin == NULL) {
                return NGX_ERROR;
            }

            sin->sin_family = AF_INET;
            sin->sin_port = port;
            sin->sin_addr.s_addr = *(in_addr_t *) (h->h_addr_list[i]);

            u->addrs[i].sockaddr = (struct sockaddr *) sin;
            u->addrs[i].socklen = sizeof(struct sockaddr_in);

            len = NGX_INET_ADDRSTRLEN + sizeof(":65535") - 1;

            p = ngx_pnalloc(pool, len);
            if (p == NULL) {
                return NGX_ERROR;
            }

            len = ngx_sock_ntop((struct sockaddr *) sin,
                                sizeof(struct sockaddr_in), p, len, 1);

            u->addrs[i].name.len = len;
            u->addrs[i].name.data = p;
        }

#if (T_NGX_DNS_RESOLVE_BACKUP)
        ph = (u_char *) getenv(NGX_DNS_RESOLVE_BACKUP_PATH);
        if (ph != NULL) {
            path.data = ph;
            path.len = ngx_strlen(ph);
            if (ngx_resolve_backup(pool, &u, path) != NGX_OK) {
                ngx_log_error(NGX_LOG_WARN, ngx_cycle->log, 0,
                              "dom %V backup local dns cache failed",
                              &u->host);
            }
        }
#endif

    } else {

        /* MP: ngx_shared_palloc() */

        u->addrs = ngx_pcalloc(pool, sizeof(ngx_addr_t));
        if (u->addrs == NULL) {
            return NGX_ERROR;
        }

        sin = ngx_pcalloc(pool, sizeof(struct sockaddr_in));
        if (sin == NULL) {
            return NGX_ERROR;
        }

        u->naddrs = 1;

        sin->sin_family = AF_INET;
        sin->sin_port = port;
        sin->sin_addr.s_addr = in_addr;

        u->addrs[0].sockaddr = (struct sockaddr *) sin;
        u->addrs[0].socklen = sizeof(struct sockaddr_in);

        p = ngx_pnalloc(pool, u->host.len + sizeof(":65535") - 1);
        if (p == NULL) {
            return NGX_ERROR;
        }

        u->addrs[0].name.len = ngx_sprintf(p, "%V:%d",
                                           &u->host, ntohs(port)) - p;
        u->addrs[0].name.data = p;
    }

    return NGX_OK;
}