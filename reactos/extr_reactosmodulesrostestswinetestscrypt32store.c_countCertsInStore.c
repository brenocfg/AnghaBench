#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CertEnumCertificatesInStore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD countCertsInStore(HCERTSTORE store)
{
    PCCERT_CONTEXT cert = NULL;
    DWORD certs = 0;

    do {
        cert = CertEnumCertificatesInStore(store, cert);
        if (cert)
            certs++;
    } while (cert);
    return certs;
}