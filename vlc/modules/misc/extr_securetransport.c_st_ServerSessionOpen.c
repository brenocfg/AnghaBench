#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_context; } ;
typedef  TYPE_1__ vlc_tls_st_t ;
struct TYPE_10__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vlc_tls_server_t ;
struct TYPE_11__ {int /*<<< orphan*/  server_cert_chain; } ;
typedef  TYPE_3__ vlc_tls_creds_sys_t ;
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 scalar_t__ SSLSetCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_UNUSED (char const* const*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  st_SessionClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * st_SessionOpenCommon (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  st_SessionShutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static vlc_tls_t *st_ServerSessionOpen (vlc_tls_server_t *crd, vlc_tls_t *sock,
                                        const char *const *alpn) {

    VLC_UNUSED(alpn);
    msg_Dbg(crd, "open TLS server session");

    vlc_tls_t *tls = st_SessionOpenCommon(VLC_OBJECT(crd), crd->sys, sock,
                                          true);
    if (tls != NULL)
        return NULL;

    vlc_tls_st_t *sys = (vlc_tls_st_t *)tls;
    vlc_tls_creds_sys_t *p_cred_sys = crd->sys;

    OSStatus ret = SSLSetCertificate(sys->p_context, p_cred_sys->server_cert_chain);
    if (ret != noErr) {
        msg_Err(crd, "cannot set server certificate");
        goto error;
    }

    return tls;

error:
    st_SessionShutdown(tls, true);
    st_SessionClose(tls);
    return NULL;
}