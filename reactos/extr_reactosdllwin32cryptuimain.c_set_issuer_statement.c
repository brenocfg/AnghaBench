#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct IssuerStatement {void* userNotice; void* cps; } ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_12__ {int dwFlags; TYPE_2__* pCertContext; } ;
struct TYPE_10__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_11__ {TYPE_3__ Value; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_9__ {TYPE_1__* pCertInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  rgExtension; int /*<<< orphan*/  cExtension; } ;
typedef  TYPE_4__* PCERT_EXTENSION ;
typedef  TYPE_5__* PCCRYPTUI_VIEWCERTIFICATE_STRUCTW ;
typedef  void* LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CRYPT_OBJID_BLOB ;
typedef  int /*<<< orphan*/  CERT_POLICIES_INFO ;

/* Variables and functions */
 int CRYPTUI_DISABLE_ISSUERSTATEMENT ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 TYPE_4__* CertFindExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWLP_USER ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct IssuerStatement* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDC_ISSUERSTATEMENT ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/ * find_policy_qualifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_cps_str_from_qualifier (int /*<<< orphan*/ *) ; 
 void* get_user_notice_from_qualifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szOID_CERT_POLICIES ; 
 int /*<<< orphan*/  szOID_PKIX_POLICY_QUALIFIER_CPS ; 
 int /*<<< orphan*/  szOID_PKIX_POLICY_QUALIFIER_USERNOTICE ; 

__attribute__((used)) static void set_issuer_statement(HWND hwnd,
 PCCRYPTUI_VIEWCERTIFICATE_STRUCTW pCertViewInfo)
{
    PCERT_EXTENSION policyExt;

    if (!(pCertViewInfo->dwFlags & CRYPTUI_DISABLE_ISSUERSTATEMENT) &&
     (policyExt = CertFindExtension(szOID_CERT_POLICIES,
     pCertViewInfo->pCertContext->pCertInfo->cExtension,
     pCertViewInfo->pCertContext->pCertInfo->rgExtension)))
    {
        CERT_POLICIES_INFO *policies;
        DWORD size;

        if (CryptDecodeObjectEx(X509_ASN_ENCODING, policyExt->pszObjId,
         policyExt->Value.pbData, policyExt->Value.cbData,
         CRYPT_DECODE_ALLOC_FLAG, NULL, &policies, &size))
        {
            CRYPT_OBJID_BLOB *qualifier;
            LPWSTR cps = NULL, userNotice = NULL;

            if ((qualifier = find_policy_qualifier(policies,
             szOID_PKIX_POLICY_QUALIFIER_CPS)))
                cps = get_cps_str_from_qualifier(qualifier);
            if ((qualifier = find_policy_qualifier(policies,
             szOID_PKIX_POLICY_QUALIFIER_USERNOTICE)))
                userNotice = get_user_notice_from_qualifier(qualifier);
            if (cps || userNotice)
            {
                struct IssuerStatement *issuerStatement =
                 HeapAlloc(GetProcessHeap(), 0, sizeof(struct IssuerStatement));

                if (issuerStatement)
                {
                    issuerStatement->cps = cps;
                    issuerStatement->userNotice = userNotice;
                    EnableWindow(GetDlgItem(hwnd, IDC_ISSUERSTATEMENT), TRUE);
                    SetWindowLongPtrW(hwnd, DWLP_USER,
                     (ULONG_PTR)issuerStatement);
                }
            }
            LocalFree(policies);
        }
    }
}