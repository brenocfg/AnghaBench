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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_MGR_CERTS ; 
 int /*<<< orphan*/  LVM_DELETEALLITEMS ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cert_mgr_current_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_certs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_store_certs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refresh_store_certs(HWND hwnd)
{
    HWND lv = GetDlgItem(hwnd, IDC_MGR_CERTS);

    free_certs(lv);
    SendMessageW(lv, LVM_DELETEALLITEMS, 0, 0);
    show_store_certs(hwnd, cert_mgr_current_store(hwnd));
}