#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pCertContext; } ;
typedef  TYPE_1__* PCCRYPTUI_VIEWCERTIFICATE_STRUCTW ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_NAME_ISSUER_FLAG ; 
 int /*<<< orphan*/  IDS_ISSUER_HEADING ; 
 int /*<<< orphan*/  IDS_SUBJECT_HEADING ; 
 int /*<<< orphan*/  set_cert_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_cert_name_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cert_validity_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_general_info(HWND hwnd,
 PCCRYPTUI_VIEWCERTIFICATE_STRUCTW pCertViewInfo)
{
    set_cert_info(hwnd, pCertViewInfo);
    set_cert_name_string(hwnd, pCertViewInfo->pCertContext, 0,
     IDS_SUBJECT_HEADING);
    set_cert_name_string(hwnd, pCertViewInfo->pCertContext,
     CERT_NAME_ISSUER_FLAG, IDS_ISSUER_HEADING);
    set_cert_validity_period(hwnd, pCertViewInfo->pCertContext);
}