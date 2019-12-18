#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_4__ {int /*<<< orphan*/  session; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ vlc_tls_gnutls_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  gnutls_session_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; scalar_t__ data; } ;
typedef  TYPE_2__ gnutls_datum_t ;

/* Variables and functions */
#define  GNUTLS_E_AGAIN 130 
#define  GNUTLS_E_INTERRUPTED 129 
#define  GNUTLS_E_SUCCESS 128 
 unsigned int GNUTLS_SFLAGS_ETM ; 
 unsigned int GNUTLS_SFLAGS_EXT_MASTER_SECRET ; 
 unsigned int GNUTLS_SFLAGS_FALSE_START ; 
 unsigned int GNUTLS_SFLAGS_SAFE_RENEGOTIATION ; 
 int gnutls_alpn_get_selected_protocol (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ gnutls_error_is_fatal (int) ; 
 int gnutls_handshake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_record_get_direction (int /*<<< orphan*/ ) ; 
 unsigned int gnutls_session_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/ * memchr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* strndup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gnutls_Handshake(vlc_tls_t *tls, char **restrict alp)
{
    vlc_tls_gnutls_t *priv = (vlc_tls_gnutls_t *)tls;
    vlc_object_t *obj = priv->obj;
    gnutls_session_t session = priv->session;
    int val = gnutls_handshake(session);

    if (gnutls_error_is_fatal(val))
    {
        msg_Err(obj, "TLS handshake error: %s", gnutls_strerror(val));
        return -1;
    }

    switch (val)
    {
        case GNUTLS_E_SUCCESS:
            break;
        case GNUTLS_E_AGAIN:
        case GNUTLS_E_INTERRUPTED:
            /* I/O event: return to caller's poll() loop */
            return 1 + gnutls_record_get_direction(session);
        default:
            msg_Warn(obj, "TLS handshake error: %s", gnutls_strerror(val));
            return 1;
    }

    msg_Dbg(obj, "TLS handshake complete");

    unsigned flags = gnutls_session_get_flags(session);

    if (flags & GNUTLS_SFLAGS_SAFE_RENEGOTIATION)
        msg_Dbg(obj, " - safe renegotiation (RFC5746) enabled");
    if (flags & GNUTLS_SFLAGS_EXT_MASTER_SECRET)
        msg_Dbg(obj, " - extended master secret (RFC7627) enabled");
    if (flags & GNUTLS_SFLAGS_ETM)
        msg_Dbg(obj, " - encrypt then MAC (RFC7366) enabled");
    if (flags & GNUTLS_SFLAGS_FALSE_START)
        msg_Dbg(obj, " - false start (RFC7918) enabled");

    if (alp != NULL)
    {
        gnutls_datum_t datum;

        val = gnutls_alpn_get_selected_protocol (session, &datum);
        if (val == 0)
        {
            if (memchr (datum.data, 0, datum.size) != NULL)
                return -1; /* Other end is doing something fishy?! */

            *alp = strndup ((char *)datum.data, datum.size);
            if (unlikely(*alp == NULL))
                return -1;
        }
        else
            *alp = NULL;
    }
    return 0;
}