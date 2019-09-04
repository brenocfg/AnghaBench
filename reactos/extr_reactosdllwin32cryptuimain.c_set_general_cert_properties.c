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
struct edit_cert_data {int /*<<< orphan*/  cert; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_DESCRIPTION_PROP_ID ; 
 int /*<<< orphan*/  CERT_FRIENDLY_NAME_PROP_ID ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_DESCRIPTION ; 
 int /*<<< orphan*/  IDC_FRIENDLY_NAME ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/ * get_cert_property_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_cert_usages (int /*<<< orphan*/ ,struct edit_cert_data*) ; 

__attribute__((used)) static void set_general_cert_properties(HWND hwnd, struct edit_cert_data *data)
{
    PCCERT_CONTEXT cert = data->cert;
    WCHAR *str;

    if ((str = get_cert_property_as_string(cert, CERT_FRIENDLY_NAME_PROP_ID)))
    {
        SendMessageW(GetDlgItem(hwnd, IDC_FRIENDLY_NAME), WM_SETTEXT, 0,
         (LPARAM)str);
        HeapFree(GetProcessHeap(), 0, str);
    }
    if ((str = get_cert_property_as_string(cert, CERT_DESCRIPTION_PROP_ID)))
    {
        SendMessageW(GetDlgItem(hwnd, IDC_DESCRIPTION), WM_SETTEXT, 0,
         (LPARAM)str);
        HeapFree(GetProcessHeap(), 0, str);
    }
    show_cert_usages(hwnd, data);
}