#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_6__ {int /*<<< orphan*/  tls; int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ vlc_tls_gnutls_t ;
struct TYPE_7__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_2__ vlc_tls_client_t ;
typedef  int /*<<< orphan*/  gnutls_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_CLIENT ; 
 int /*<<< orphan*/  GNUTLS_NAME_DNS ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 TYPE_1__* gnutls_SessionOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const* const*) ; 
 int /*<<< orphan*/  gnutls_dh_set_prime_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gnutls_server_name_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static vlc_tls_t *gnutls_ClientSessionOpen(vlc_tls_client_t *crd,
                                           vlc_tls_t *sk, const char *hostname,
                                           const char *const *alpn)
{
    vlc_tls_gnutls_t *priv = gnutls_SessionOpen(VLC_OBJECT(crd), GNUTLS_CLIENT,
                                                crd->sys, sk, alpn);
    if (priv == NULL)
        return NULL;

    gnutls_session_t session = priv->session;

    /* minimum DH prime bits */
    gnutls_dh_set_prime_bits (session, 1024);

    if (likely(hostname != NULL))
        /* fill Server Name Indication */
        gnutls_server_name_set (session, GNUTLS_NAME_DNS,
                                hostname, strlen (hostname));

    return &priv->tls;
}