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
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int LB_ERR ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void PropDlg_DisplayValue(HWND hlbox, HWND hedit)
{
	int idx = SendMessageW(hlbox, LB_GETCURSEL, 0, 0);

	if (idx != LB_ERR) {
		LPCWSTR pValue = (LPCWSTR)SendMessageW(hlbox, LB_GETITEMDATA, idx, 0);

		if (pValue)
			SetWindowTextW(hedit, pValue);
	}
}