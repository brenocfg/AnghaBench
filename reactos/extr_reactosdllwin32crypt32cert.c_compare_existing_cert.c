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
struct TYPE_3__ {int /*<<< orphan*/  pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
typedef  TYPE_1__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CertCompareCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL compare_existing_cert(PCCERT_CONTEXT pCertContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    PCCERT_CONTEXT toCompare = pvPara;
    return CertCompareCertificate(pCertContext->dwCertEncodingType,
     pCertContext->pCertInfo, toCompare->pCertInfo);
}