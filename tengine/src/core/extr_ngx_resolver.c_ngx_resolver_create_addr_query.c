#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  void* u_char ;
struct TYPE_9__ {int* s6_addr; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_resolver_t ;
typedef  int /*<<< orphan*/  ngx_resolver_qs_t ;
struct TYPE_12__ {void** query; scalar_t__ qlen; } ;
typedef  TYPE_4__ ngx_resolver_node_t ;
struct TYPE_13__ {int flags_hi; int nqs_lo; scalar_t__ nar_lo; scalar_t__ nar_hi; scalar_t__ nns_lo; scalar_t__ nns_hi; scalar_t__ nan_lo; scalar_t__ nan_hi; scalar_t__ nqs_hi; scalar_t__ flags_lo; void* ident_lo; void* ident_hi; } ;
typedef  TYPE_5__ ngx_resolver_hdr_t ;
struct TYPE_14__ {TYPE_2__* sockaddr; } ;
typedef  TYPE_6__ ngx_resolver_addr_t ;
typedef  size_t ngx_int_t ;
typedef  size_t in_addr_t ;
struct TYPE_10__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET6 128 
 size_t NGX_ERROR ; 
 size_t NGX_OK ; 
 void** ngx_cpymem (void**,char*,int) ; 
 int ngx_random () ; 
 void** ngx_resolver_alloc (int /*<<< orphan*/ *,size_t) ; 
 void** ngx_sprintf (void**,char*,size_t,...) ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_resolver_create_addr_query(ngx_resolver_t *r, ngx_resolver_node_t *rn,
    ngx_resolver_addr_t *addr)
{
    u_char               *p, *d;
    size_t                len;
    in_addr_t             inaddr;
    ngx_int_t             n;
    ngx_uint_t            ident;
    ngx_resolver_hdr_t   *query;
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
#endif

    switch (addr->sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        len = sizeof(ngx_resolver_hdr_t)
              + 64 + sizeof(".ip6.arpa.") - 1
              + sizeof(ngx_resolver_qs_t);

        break;
#endif

    default: /* AF_INET */
        len = sizeof(ngx_resolver_hdr_t)
              + sizeof(".255.255.255.255.in-addr.arpa.") - 1
              + sizeof(ngx_resolver_qs_t);
    }

    p = ngx_resolver_alloc(r, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    rn->query = p;
    query = (ngx_resolver_hdr_t *) p;

    ident = ngx_random();

    query->ident_hi = (u_char) ((ident >> 8) & 0xff);
    query->ident_lo = (u_char) (ident & 0xff);

    /* recursion query */
    query->flags_hi = 1; query->flags_lo = 0;

    /* one question */
    query->nqs_hi = 0; query->nqs_lo = 1;
    query->nan_hi = 0; query->nan_lo = 0;
    query->nns_hi = 0; query->nns_lo = 0;
    query->nar_hi = 0; query->nar_lo = 0;

    p += sizeof(ngx_resolver_hdr_t);

    switch (addr->sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) addr->sockaddr;

        for (n = 15; n >= 0; n--) {
            p = ngx_sprintf(p, "\1%xd\1%xd",
                            sin6->sin6_addr.s6_addr[n] & 0xf,
                            (sin6->sin6_addr.s6_addr[n] >> 4) & 0xf);
        }

        p = ngx_cpymem(p, "\3ip6\4arpa\0", 10);

        break;
#endif

    default: /* AF_INET */

        sin = (struct sockaddr_in *) addr->sockaddr;
        inaddr = ntohl(sin->sin_addr.s_addr);

        for (n = 0; n < 32; n += 8) {
            d = ngx_sprintf(&p[1], "%ud", (inaddr >> n) & 0xff);
            *p = (u_char) (d - &p[1]);
            p = d;
        }

        p = ngx_cpymem(p, "\7in-addr\4arpa\0", 14);
    }

    /* query type "PTR", IN query class */
    p = ngx_cpymem(p, "\0\14\0\1", 4);

    rn->qlen = (u_short) (p - rn->query);

    return NGX_OK;
}