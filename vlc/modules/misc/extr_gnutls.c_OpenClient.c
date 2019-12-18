#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sys; int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ vlc_tls_client_t ;
typedef  int /*<<< orphan*/  gnutls_certificate_credentials_t ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_PEM ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gnutls_Banner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_ClientOps ; 
 int gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_certificate_set_verify_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_system_trust (int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_trust_dir (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*,...) ; 
 scalar_t__ var_InheritBool (TYPE_1__*,char*) ; 
 char* var_InheritString (TYPE_1__*,char*) ; 

__attribute__((used)) static int OpenClient(vlc_tls_client_t *crd)
{
    gnutls_certificate_credentials_t x509;

    gnutls_Banner(VLC_OBJECT(crd));

    int val = gnutls_certificate_allocate_credentials (&x509);
    if (val != 0)
    {
        msg_Err (crd, "cannot allocate credentials: %s",
                 gnutls_strerror (val));
        return VLC_EGENERIC;
    }

    if (var_InheritBool(crd, "gnutls-system-trust"))
    {
        val = gnutls_certificate_set_x509_system_trust(x509);
        if (val < 0)
            msg_Err(crd, "cannot load trusted Certificate Authorities "
                    "from %s: %s", "system", gnutls_strerror(val));
        else
            msg_Dbg(crd, "loaded %d trusted CAs from %s", val, "system");
    }

    char *dir = var_InheritString(crd, "gnutls-dir-trust");
    if (dir != NULL)
    {
        val = gnutls_certificate_set_x509_trust_dir(x509, dir,
                                                    GNUTLS_X509_FMT_PEM);
        if (val < 0)
            msg_Err(crd, "cannot load trusted Certificate Authorities "
                    "from %s: %s", dir, gnutls_strerror(val));
        else
            msg_Dbg(crd, "loaded %d trusted CAs from %s", val, dir);
        free(dir);
    }

    gnutls_certificate_set_verify_flags (x509,
                                         GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT);

    crd->ops = &gnutls_ClientOps;
    crd->sys = x509;
    return VLC_SUCCESS;
}