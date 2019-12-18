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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WC_COMBOBOXEXA ; 
 int /*<<< orphan*/  hComboExParentWnd ; 
 int /*<<< orphan*/  hMainHinst ; 

__attribute__((used)) static HWND createComboEx(DWORD style) {
   return CreateWindowExA(0, WC_COMBOBOXEXA, NULL, style, 0, 0, 300, 300,
            hComboExParentWnd, NULL, hMainHinst, NULL);
}