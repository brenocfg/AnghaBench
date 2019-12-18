#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_9__ {int /*<<< orphan*/  session; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ vlc_tls_gnutls_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int time_t ;
typedef  int /*<<< orphan*/  gnutls_x509_crt_t ;
typedef  int /*<<< orphan*/  gnutls_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ gnutls_datum_t ;

/* Variables and functions */
 unsigned int GNUTLS_CERT_INVALID ; 
 unsigned int GNUTLS_CERT_SIGNER_NOT_FOUND ; 
 unsigned int GNUTLS_CERT_UNEXPECTED_OWNER ; 
 int /*<<< orphan*/  GNUTLS_CRT_PRINT_ONELINE ; 
 int /*<<< orphan*/  GNUTLS_CRT_X509 ; 
#define  GNUTLS_E_CERTIFICATE_KEY_MISMATCH 129 
#define  GNUTLS_E_NO_CERTIFICATE_FOUND 128 
 int /*<<< orphan*/  GNUTLS_X509_FMT_DER ; 
 char* N_ (char*) ; 
 int /*<<< orphan*/  VLC_DIALOG_QUESTION_WARNING ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int gnutls_Handshake (int /*<<< orphan*/ *,char**) ; 
 TYPE_2__* gnutls_certificate_get_peers (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  gnutls_certificate_type_get (int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_certificate_verification_status_print (unsigned int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_verify_peers3 (int /*<<< orphan*/ ,char const*,unsigned int*) ; 
 int /*<<< orphan*/  gnutls_free (int /*<<< orphan*/ ) ; 
 int gnutls_store_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,TYPE_2__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int gnutls_verify_stored_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_deinit (int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_x509_crt_import (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_x509_crt_init (int /*<<< orphan*/ *) ; 
 scalar_t__ gnutls_x509_crt_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  time (int*) ; 
 int vlc_dialog_wait_question (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_gettext (char const*) ; 

__attribute__((used)) static int gnutls_ClientHandshake(vlc_tls_t *tls,
                                  const char *host, const char *service,
                                  char **restrict alp)
{
    vlc_tls_gnutls_t *priv = (vlc_tls_gnutls_t *)tls;
    vlc_object_t *obj = priv->obj;

    int val = gnutls_Handshake(tls, alp);
    if (val)
        return val;

    /* certificates chain verification */
    gnutls_session_t session = priv->session;
    unsigned status;

    val = gnutls_certificate_verify_peers3 (session, host, &status);
    if (val)
    {
        msg_Err(obj, "Certificate verification error: %s",
                gnutls_strerror(val));
        goto error;
    }

    if (status == 0) /* Good certificate */
        return 0;

    /* Bad certificate */
    gnutls_datum_t desc;

    if (gnutls_certificate_verification_status_print(status,
                         gnutls_certificate_type_get (session), &desc, 0) == 0)
    {
        msg_Err(obj, "Certificate verification failure: %s", desc.data);
        gnutls_free (desc.data);
    }

    status &= ~GNUTLS_CERT_INVALID; /* always set / catch-all error */
    status &= ~GNUTLS_CERT_SIGNER_NOT_FOUND; /* unknown CA */
    status &= ~GNUTLS_CERT_UNEXPECTED_OWNER; /* mismatched hostname */

    if (status != 0 || host == NULL)
        goto error; /* Really bad certificate */

    /* Look up mismatching certificate in store */
    const gnutls_datum_t *datum;
    unsigned count;

    datum = gnutls_certificate_get_peers (session, &count);
    if (datum == NULL || count == 0)
    {
        msg_Err(obj, "Peer certificate not available");
        goto error;
    }

    msg_Dbg(obj, "%u certificate(s) in the list", count);
    val = gnutls_verify_stored_pubkey (NULL, NULL, host, service,
                                       GNUTLS_CRT_X509, datum, 0);
    const char *msg;
    switch (val)
    {
        case 0:
            msg_Dbg(obj, "certificate key match for %s", host);
            return 0;
        case GNUTLS_E_NO_CERTIFICATE_FOUND:
            msg_Dbg(obj, "no known certificates for %s", host);
            msg = N_("However, the security certificate presented by the "
                "server is unknown and could not be authenticated by any "
                "trusted Certificate Authority.");
            break;
        case GNUTLS_E_CERTIFICATE_KEY_MISMATCH:
            msg_Dbg(obj, "certificate keys mismatch for %s", host);
            msg = N_("However, the security certificate presented by the "
                "server changed since the previous visit and was not "
                "authenticated by any trusted Certificate Authority.");
            break;
        default:
            msg_Err(obj, "certificate key match error for %s: %s", host,
                    gnutls_strerror(val));
            goto error;
    }

    if (vlc_dialog_wait_question(obj, VLC_DIALOG_QUESTION_WARNING,
            _("Abort"), _("View certificate"), NULL,
            _("Insecure site"),
            _("You attempted to reach %s. %s\n"
            "This problem may be stem from an attempt to breach your security, "
            "compromise your privacy, or a configuration error.\n\n"
            "If in doubt, abort now.\n"), host, vlc_gettext(msg)) != 1)
        goto error;

    gnutls_x509_crt_t cert;

    if (gnutls_x509_crt_init (&cert))
        goto error;
    if (gnutls_x509_crt_import (cert, datum, GNUTLS_X509_FMT_DER)
     || gnutls_x509_crt_print (cert, GNUTLS_CRT_PRINT_ONELINE, &desc))
    {
        gnutls_x509_crt_deinit (cert);
        goto error;
    }
    gnutls_x509_crt_deinit (cert);

    val = vlc_dialog_wait_question(obj, VLC_DIALOG_QUESTION_WARNING,
            _("Abort"), _("Accept 24 hours"), _("Accept permanently"),
            _("Insecure site"),
            _("This is the certificate presented by %s:\n%s\n\n"
            "If in doubt, abort now.\n"), host, desc.data);
    gnutls_free (desc.data);

    time_t expiry = 0;
    switch (val)
    {
        case 1:
            time (&expiry);
            expiry += 24 * 60 * 60;
            /* fall through */
        case 2:
            val = gnutls_store_pubkey (NULL, NULL, host, service,
                                       GNUTLS_CRT_X509, datum, expiry, 0);
            if (val)
                msg_Err(obj, "cannot store X.509 certificate: %s",
                         gnutls_strerror (val));
            break;
        default:
            goto error;
    }
    return 0;

error:
    if (alp != NULL)
        free(*alp);
    return -1;
}