#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* p; } ;
typedef  TYPE_2__ vlc_tls_t ;
struct TYPE_12__ {TYPE_1__* ops; } ;
typedef  TYPE_3__ vlc_tls_server_t ;
struct TYPE_10__ {TYPE_2__* (* open ) (TYPE_3__*,TYPE_2__*,char const* const*) ;} ;

/* Variables and functions */
 TYPE_2__* stub1 (TYPE_3__*,TYPE_2__*,char const* const*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

vlc_tls_t *vlc_tls_ServerSessionCreate(vlc_tls_server_t *crd,
                                       vlc_tls_t *sock,
                                       const char *const *alpn)
{
    int canc = vlc_savecancel();
    vlc_tls_t *session = crd->ops->open(crd, sock, alpn);
    vlc_restorecancel(canc);
    if (session != NULL)
        session->p = sock;
    return session;
}