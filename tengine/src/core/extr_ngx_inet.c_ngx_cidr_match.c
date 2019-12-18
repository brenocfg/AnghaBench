#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct in6_addr {int* s6_addr; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_10__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {size_t sa_family; } ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int mask; int addr; } ;
struct TYPE_12__ {int* s6_addr; } ;
struct TYPE_11__ {int* s6_addr; } ;
struct TYPE_13__ {TYPE_3__ addr; TYPE_2__ mask; } ;
struct TYPE_15__ {TYPE_5__ in; TYPE_4__ in6; } ;
struct TYPE_16__ {size_t family; TYPE_6__ u; } ;
typedef  TYPE_7__ ngx_cidr_t ;
struct TYPE_17__ {size_t nelts; TYPE_7__* elts; } ;
typedef  TYPE_8__ ngx_array_t ;
typedef  int in_addr_t ;

/* Variables and functions */
 size_t AF_INET ; 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_OK ; 
 int htonl (int) ; 

ngx_int_t
ngx_cidr_match(struct sockaddr *sa, ngx_array_t *cidrs)
{
#if (NGX_HAVE_INET6)
    u_char           *p;
#endif
    in_addr_t         inaddr;
    ngx_cidr_t       *cidr;
    ngx_uint_t        family, i;
#if (NGX_HAVE_INET6)
    ngx_uint_t        n;
    struct in6_addr  *inaddr6;
#endif

#if (NGX_SUPPRESS_WARN)
    inaddr = 0;
#if (NGX_HAVE_INET6)
    inaddr6 = NULL;
#endif
#endif

    family = sa->sa_family;

    if (family == AF_INET) {
        inaddr = ((struct sockaddr_in *) sa)->sin_addr.s_addr;
    }

#if (NGX_HAVE_INET6)
    else if (family == AF_INET6) {
        inaddr6 = &((struct sockaddr_in6 *) sa)->sin6_addr;

        if (IN6_IS_ADDR_V4MAPPED(inaddr6)) {
            family = AF_INET;

            p = inaddr6->s6_addr;

            inaddr = p[12] << 24;
            inaddr += p[13] << 16;
            inaddr += p[14] << 8;
            inaddr += p[15];

            inaddr = htonl(inaddr);
        }
    }
#endif

    for (cidr = cidrs->elts, i = 0; i < cidrs->nelts; i++) {
        if (cidr[i].family != family) {
            goto next;
        }

        switch (family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            for (n = 0; n < 16; n++) {
                if ((inaddr6->s6_addr[n] & cidr[i].u.in6.mask.s6_addr[n])
                    != cidr[i].u.in6.addr.s6_addr[n])
                {
                    goto next;
                }
            }
            break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
        case AF_UNIX:
            break;
#endif

        default: /* AF_INET */
            if ((inaddr & cidr[i].u.in.mask) != cidr[i].u.in.addr) {
                goto next;
            }
            break;
        }

        return NGX_OK;

    next:
        continue;
    }

    return NGX_DECLINED;
}