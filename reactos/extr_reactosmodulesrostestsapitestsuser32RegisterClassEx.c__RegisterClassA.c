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
typedef  TYPE_1__ WNDCLASSEXA ;
typedef  int /*<<< orphan*/  WNDCLASSEX ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 int /*<<< orphan*/  RegisterClassExA (TYPE_1__*) ; 

__attribute__((used)) static ATOM _RegisterClassA(LPCSTR lpzClassName, HINSTANCE hInstance, UINT style, WNDPROC lpfnWndProc)
{
    WNDCLASSEXA wcex = {sizeof(WNDCLASSEX), style, lpfnWndProc};
    wcex.lpszClassName  = lpzClassName;
    wcex.hInstance      = hInstance;
    return RegisterClassExA(&wcex);
}