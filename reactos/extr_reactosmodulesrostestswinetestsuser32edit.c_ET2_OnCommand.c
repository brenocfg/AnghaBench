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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ EN_UPDATE ; 
 int /*<<< orphan*/  ET2_check_change () ; 
 int ID_EDITTEST2 ; 

__attribute__((used)) static void ET2_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id==ID_EDITTEST2 && codeNotify == EN_UPDATE)
        ET2_check_change();
}