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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  dwCertEncodingType; TYPE_1__* pCertInfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  Issuer; int /*<<< orphan*/  Subject; } ;
typedef  int /*<<< orphan*/ * PCERT_NAME_BLOB ;
typedef  TYPE_2__* PCCERT_CONTEXT ;
typedef  scalar_t__* LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CERT_INFO_SUBJECT_FLAG ; 
 int /*<<< orphan*/  CERT_SIMPLE_NAME_STR ; 
 int CertNameToStrW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strstrW (scalar_t__*,void const*) ; 
 scalar_t__ tolowerW (scalar_t__) ; 

__attribute__((used)) static BOOL compare_cert_by_name_str(PCCERT_CONTEXT pCertContext,
 DWORD dwType, DWORD dwFlags, const void *pvPara)
{
    PCERT_NAME_BLOB name;
    DWORD len;
    BOOL ret = FALSE;

    if (dwType & CERT_INFO_SUBJECT_FLAG)
        name = &pCertContext->pCertInfo->Subject;
    else
        name = &pCertContext->pCertInfo->Issuer;
    len = CertNameToStrW(pCertContext->dwCertEncodingType, name,
     CERT_SIMPLE_NAME_STR, NULL, 0);
    if (len)
    {
        LPWSTR str = CryptMemAlloc(len * sizeof(WCHAR));

        if (str)
        {
            LPWSTR ptr;

            CertNameToStrW(pCertContext->dwCertEncodingType, name,
             CERT_SIMPLE_NAME_STR, str, len);
            for (ptr = str; *ptr; ptr++)
                *ptr = tolowerW(*ptr);
            if (strstrW(str, pvPara))
                ret = TRUE;
            CryptMemFree(str);
        }
    }
    return ret;
}