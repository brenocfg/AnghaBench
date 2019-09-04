#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parFmt ;
struct TYPE_6__ {int cbSize; int /*<<< orphan*/  dxStartIndent; int /*<<< orphan*/  dwMask; } ;
struct TYPE_5__ {size_t cPurposes; int /*<<< orphan*/  pCertContext; int /*<<< orphan*/ * rgszPurposes; } ;
typedef  TYPE_1__* PCCRYPTUI_VIEWCERTIFICATE_STRUCTW ;
typedef  TYPE_2__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDS_CERT_INFO_BAD_PURPOSES ; 
 int /*<<< orphan*/  MY_INDENT ; 
 int /*<<< orphan*/  PFM_STARTINDENT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_string_resource_with_paraformat_to_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  display_app_usages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ display_cert_usages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_ANY_APPLICATION_POLICY ; 
 int /*<<< orphan*/  szOID_ANY_CERT_POLICY ; 

__attribute__((used)) static void set_policy_text(HWND text,
 PCCRYPTUI_VIEWCERTIFICATE_STRUCTW pCertViewInfo)
{
    BOOL includeCertUsages = FALSE, includeAppUsages = FALSE;
    BOOL badUsages = FALSE, anyUsageAdded = FALSE;

    if (pCertViewInfo->cPurposes)
    {
        DWORD i;

        for (i = 0; i < pCertViewInfo->cPurposes; i++)
        {
            if (!strcmp(pCertViewInfo->rgszPurposes[i], szOID_ANY_CERT_POLICY))
                includeCertUsages = TRUE;
            else if (!strcmp(pCertViewInfo->rgszPurposes[i],
             szOID_ANY_APPLICATION_POLICY))
                includeAppUsages = TRUE;
            else
                badUsages = TRUE;
        }
    }
    else
        includeAppUsages = includeCertUsages = TRUE;
    if (includeAppUsages)
        display_app_usages(text, pCertViewInfo->pCertContext, &anyUsageAdded);
    if (includeCertUsages)
        badUsages = display_cert_usages(text, pCertViewInfo->pCertContext,
         &anyUsageAdded);
    if (badUsages)
    {
        PARAFORMAT2 parFmt;

        parFmt.cbSize = sizeof(parFmt);
        parFmt.dwMask = PFM_STARTINDENT;
        parFmt.dxStartIndent = MY_INDENT;
        add_string_resource_with_paraformat_to_control(text,
         IDS_CERT_INFO_BAD_PURPOSES, &parFmt);
    }
}