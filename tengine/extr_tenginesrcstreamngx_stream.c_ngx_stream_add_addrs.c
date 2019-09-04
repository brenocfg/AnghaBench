#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {int naddrs; TYPE_7__* addrs; } ;
typedef  TYPE_6__ ngx_stream_port_t ;
struct TYPE_17__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {TYPE_4__ addr_text; int /*<<< orphan*/  proxy_protocol; int /*<<< orphan*/  ctx; } ;
struct TYPE_20__ {TYPE_5__ conf; int /*<<< orphan*/  addr; } ;
typedef  TYPE_7__ ngx_stream_in_addr_t ;
struct TYPE_15__ {int /*<<< orphan*/  sockaddr; struct sockaddr_in sockaddr_in; } ;
struct TYPE_16__ {int /*<<< orphan*/  socklen; TYPE_2__ sockaddr; int /*<<< orphan*/  proxy_protocol; int /*<<< orphan*/  ctx; } ;
struct TYPE_21__ {TYPE_3__ opt; } ;
typedef  TYPE_8__ ngx_stream_conf_addr_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_9__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_7__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 size_t ngx_sock_ntop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_add_addrs(ngx_conf_t *cf, ngx_stream_port_t *stport,
    ngx_stream_conf_addr_t *addr)
{
    u_char                *p;
    size_t                 len;
    ngx_uint_t             i;
    struct sockaddr_in    *sin;
    ngx_stream_in_addr_t  *addrs;
    u_char                 buf[NGX_SOCKADDR_STRLEN];
#if (NGX_STREAM_SNI)
    ngx_stream_virtual_names_t  *vn;
#endif

    stport->addrs = ngx_pcalloc(cf->pool,
                                stport->naddrs * sizeof(ngx_stream_in_addr_t));
    if (stport->addrs == NULL) {
        return NGX_ERROR;
    }

    addrs = stport->addrs;

    for (i = 0; i < stport->naddrs; i++) {

        sin = &addr[i].opt.sockaddr.sockaddr_in;
        addrs[i].addr = sin->sin_addr.s_addr;

        addrs[i].conf.ctx = addr[i].opt.ctx;
#if (NGX_STREAM_SSL)
        addrs[i].conf.ssl = addr[i].opt.ssl;
#endif
        addrs[i].conf.proxy_protocol = addr[i].opt.proxy_protocol;

        len = ngx_sock_ntop(&addr[i].opt.sockaddr.sockaddr, addr[i].opt.socklen,
                            buf, NGX_SOCKADDR_STRLEN, 1);

        p = ngx_pnalloc(cf->pool, len);
        if (p == NULL) {
            return NGX_ERROR;
        }

        ngx_memcpy(p, buf, len);

        addrs[i].conf.addr_text.len = len;
        addrs[i].conf.addr_text.data = p;

#if (NGX_STREAM_SNI)
        addrs[i].conf.default_server = addr[i].default_server;

        if (addr[i].hash.buckets == NULL
            && (addr[i].wc_head == NULL
                || addr[i].wc_head->hash.buckets == NULL)
            && (addr[i].wc_tail == NULL
                || addr[i].wc_tail->hash.buckets == NULL)
            )
        {
            continue;
        }

        vn = ngx_palloc(cf->pool, sizeof(ngx_stream_virtual_names_t));
        if (vn == NULL) {
            return NGX_ERROR;
        }

        addrs[i].conf.virtual_names = vn;

        vn->names.hash = addr[i].hash;
        vn->names.wc_head = addr[i].wc_head;
        vn->names.wc_tail = addr[i].wc_tail;
#endif
    }

    return NGX_OK;
}