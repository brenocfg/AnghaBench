#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_3__ {int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ vlc_tls_gnutls_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  gnutls_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_SHUT_RDWR ; 
 int /*<<< orphan*/  GNUTLS_SHUT_WR ; 
 int gnutls_Error (TYPE_1__*,scalar_t__) ; 
 scalar_t__ gnutls_bye (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_record_uncork (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gnutls_Shutdown(vlc_tls_t *tls, bool duplex)
{
    vlc_tls_gnutls_t *priv = (vlc_tls_gnutls_t *)tls;
    gnutls_session_t session = priv->session;
    ssize_t val;

    /* Flush any pending data */
    val = gnutls_record_uncork(session, 0);
    if (val < 0)
        return gnutls_Error(priv, val);

    val = gnutls_bye(session, duplex ? GNUTLS_SHUT_RDWR : GNUTLS_SHUT_WR);
    if (val < 0)
        return gnutls_Error(priv, val);

    return 0;
}