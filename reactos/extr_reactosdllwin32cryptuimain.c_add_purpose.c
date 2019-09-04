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
struct TYPE_5__ {int mask; char* pszText; scalar_t__ lParam; scalar_t__ iSubItem; int /*<<< orphan*/  iItem; int /*<<< orphan*/  stateMask; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int cbSize; char* pszOID; } ;
typedef  TYPE_1__* PCRYPT_OID_INFO ;
typedef  TYPE_2__ LVITEMA ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  CRYPT_OID_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CheckBitmapIndexChecked ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_CERTIFICATE_USAGES ; 
 int /*<<< orphan*/  INDEXTOSTATEIMAGEMASK (int /*<<< orphan*/ ) ; 
 int LVIF_PARAM ; 
 int LVIF_STATE ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  LVIS_STATEIMAGEMASK ; 
 int /*<<< orphan*/  LVM_GETITEMCOUNT ; 
 int /*<<< orphan*/  LVM_INSERTITEMA ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_purpose(HWND hwnd, LPCSTR oid)
{
    HWND lv = GetDlgItem(hwnd, IDC_CERTIFICATE_USAGES);
    PCRYPT_OID_INFO info = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
     sizeof(CRYPT_OID_INFO));

    if (info)
    {
        char *oidCopy = HeapAlloc(GetProcessHeap(), 0, strlen(oid) + 1);

        if (oidCopy)
        {
            LVITEMA item;

            strcpy(oidCopy, oid);
            info->cbSize = sizeof(CRYPT_OID_INFO);
            info->pszOID = oidCopy;
            item.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM;
            item.state = INDEXTOSTATEIMAGEMASK(CheckBitmapIndexChecked);
            item.stateMask = LVIS_STATEIMAGEMASK;
            item.iItem = SendMessageW(lv, LVM_GETITEMCOUNT, 0, 0);
            item.iSubItem = 0;
            item.lParam = (LPARAM)info;
            item.pszText = oidCopy;
            SendMessageA(lv, LVM_INSERTITEMA, 0, (LPARAM)&item);
        }
        else
            HeapFree(GetProcessHeap(), 0, info);
    }
}