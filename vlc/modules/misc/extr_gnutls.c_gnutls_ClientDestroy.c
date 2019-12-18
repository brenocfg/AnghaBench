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
struct TYPE_3__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_1__ vlc_tls_client_t ;
typedef  int /*<<< orphan*/  gnutls_certificate_credentials_t ;

/* Variables and functions */
 int /*<<< orphan*/  gnutls_certificate_free_credentials (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gnutls_ClientDestroy(vlc_tls_client_t *crd)
{
    gnutls_certificate_credentials_t x509 = crd->sys;

    gnutls_certificate_free_credentials(x509);
}