#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hCertStore; } ;
typedef  TYPE_1__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_1__* CertEnumCertificatesInStore (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_remote_cert(PCCERT_CONTEXT remote_cert)
{
    PCCERT_CONTEXT iter = NULL;
    BOOL incl_remote = FALSE;
    unsigned cert_cnt = 0;

    ok(remote_cert->hCertStore != NULL, "hCertStore == NULL\n");

    while((iter = CertEnumCertificatesInStore(remote_cert->hCertStore, iter))) {
        if(iter == remote_cert)
            incl_remote = TRUE;
        cert_cnt++;
    }

    ok(cert_cnt == 4, "cert_cnt = %u\n", cert_cnt);
    ok(incl_remote, "context does not contain cert itself\n");
}