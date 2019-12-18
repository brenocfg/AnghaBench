#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_16__ {int* s6_addr; } ;
struct sockaddr_in6 {TYPE_15__ sin6_addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct TYPE_20__ {TYPE_3__* connection; } ;
typedef  TYPE_4__ ngx_stream_session_t ;
struct TYPE_21__ {int /*<<< orphan*/  rules_un; int /*<<< orphan*/  rules6; int /*<<< orphan*/  rules; } ;
typedef  TYPE_5__ ngx_stream_access_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int in_addr_t ;
struct TYPE_19__ {TYPE_2__* sockaddr; } ;
struct TYPE_18__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (TYPE_15__*) ; 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ngx_stream_access_inet (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_access_inet6 (TYPE_4__*,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  ngx_stream_access_module ; 
 int /*<<< orphan*/  ngx_stream_access_unix (TYPE_4__*,TYPE_5__*) ; 
 TYPE_5__* ngx_stream_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_access_handler(ngx_stream_session_t *s)
{
    struct sockaddr_in            *sin;
    ngx_stream_access_srv_conf_t  *ascf;
#if (NGX_HAVE_INET6)
    u_char                        *p;
    in_addr_t                      addr;
    struct sockaddr_in6           *sin6;
#endif

    ascf = ngx_stream_get_module_srv_conf(s, ngx_stream_access_module);

    switch (s->connection->sockaddr->sa_family) {

    case AF_INET:
        if (ascf->rules) {
            sin = (struct sockaddr_in *) s->connection->sockaddr;
            return ngx_stream_access_inet(s, ascf, sin->sin_addr.s_addr);
        }
        break;

#if (NGX_HAVE_INET6)

    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) s->connection->sockaddr;
        p = sin6->sin6_addr.s6_addr;

        if (ascf->rules && IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
            addr = p[12] << 24;
            addr += p[13] << 16;
            addr += p[14] << 8;
            addr += p[15];
            return ngx_stream_access_inet(s, ascf, htonl(addr));
        }

        if (ascf->rules6) {
            return ngx_stream_access_inet6(s, ascf, p);
        }

        break;

#endif

#if (NGX_HAVE_UNIX_DOMAIN)

    case AF_UNIX:
        if (ascf->rules_un) {
            return ngx_stream_access_unix(s, ascf);
        }

        break;

#endif
    }

    return NGX_DECLINED;
}