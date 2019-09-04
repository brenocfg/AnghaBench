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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ pwszName; } ;
typedef  TYPE_1__* PCCRYPT_OID_INFO ;
typedef  scalar_t__* LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CB_INSERTSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  CRYPT_OID_INFO_OID_KEY ; 
 TYPE_1__* CryptFindOIDInfo (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IDC_MGR_PURPOSE_SELECTION ; 
 int /*<<< orphan*/  IDS_PURPOSE_ADVANCED ; 
 int /*<<< orphan*/  IDS_PURPOSE_ALL ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 scalar_t__ PurposeFilterShowAdvanced ; 
 scalar_t__ PurposeFilterShowAll ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__* get_cert_mgr_usages () ; 
 int /*<<< orphan*/  hInstance ; 
 scalar_t__* strchr (scalar_t__*,char) ; 

__attribute__((used)) static void initialize_purpose_selection(HWND hwnd)
{
    HWND cb = GetDlgItem(hwnd, IDC_MGR_PURPOSE_SELECTION);
    WCHAR buf[MAX_STRING_LEN];
    LPSTR usages;
    int index;

    LoadStringW(hInstance, IDS_PURPOSE_ALL, buf, ARRAY_SIZE(buf));
    index = SendMessageW(cb, CB_INSERTSTRING, -1, (LPARAM)buf);
    SendMessageW(cb, CB_SETITEMDATA, index, (LPARAM)PurposeFilterShowAll);
    LoadStringW(hInstance, IDS_PURPOSE_ADVANCED, buf, ARRAY_SIZE(buf));
    index = SendMessageW(cb, CB_INSERTSTRING, -1, (LPARAM)buf);
    SendMessageW(cb, CB_SETITEMDATA, index, (LPARAM)PurposeFilterShowAdvanced);
    SendMessageW(cb, CB_SETCURSEL, 0, 0);
    if ((usages = get_cert_mgr_usages()))
    {
        LPSTR ptr, comma;

        for (ptr = usages, comma = strchr(ptr, ','); ptr && *ptr;
         ptr = comma ? comma + 1 : NULL,
         comma = ptr ? strchr(ptr, ',') : NULL)
        {
            PCCRYPT_OID_INFO info;

            if (comma)
                *comma = 0;
            if ((info = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, ptr, 0)))
            {
                index = SendMessageW(cb, CB_INSERTSTRING, 0,
                 (LPARAM)info->pwszName);
                SendMessageW(cb, CB_SETITEMDATA, index, (LPARAM)info);
            }
        }
        HeapFree(GetProcessHeap(), 0, usages);
    }
}