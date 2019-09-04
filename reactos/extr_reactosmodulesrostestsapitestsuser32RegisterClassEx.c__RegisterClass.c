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
typedef  int /*<<< orphan*/  WNDPROC ;
struct TYPE_3__ {int member_0; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lpszClassName; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ WNDCLASSEXW ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 int /*<<< orphan*/  RegisterClassExW (TYPE_1__*) ; 

__attribute__((used)) static ATOM _RegisterClass(LPCWSTR lpwszClassName, HINSTANCE hInstance, UINT style, WNDPROC lpfnWndProc)
{
    WNDCLASSEXW wcex = {sizeof(WNDCLASSEXW), style, lpfnWndProc};
    wcex.lpszClassName  = lpwszClassName;
    wcex.hInstance      = hInstance;
    return RegisterClassExW(&wcex);
}