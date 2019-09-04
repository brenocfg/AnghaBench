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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ MAKEINTATOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atRefDataProp ; 

void THEMING_SetSubclassData (HWND wnd, ULONG_PTR refData)
{
    SetPropW (wnd, (LPCWSTR)MAKEINTATOM(atRefDataProp), (HANDLE)refData);
}