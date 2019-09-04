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
struct TYPE_3__ {char* lpszClassName; int /*<<< orphan*/ * lpszMenuName; int /*<<< orphan*/  hbrBackground; int /*<<< orphan*/  hCursor; scalar_t__ hIcon; int /*<<< orphan*/  hInstance; scalar_t__ cbWndExtra; scalar_t__ cbClsExtra; int /*<<< orphan*/  lpfnWndProc; scalar_t__ style; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_ARROW ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  test_parent_wndproc ; 

__attribute__((used)) static void register_parent_class(void)
{
    WNDCLASSA cls;

    cls.style = 0;
    cls.lpfnWndProc = test_parent_wndproc;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hCursor = LoadCursorA(0, (LPCSTR)IDC_ARROW);
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "TestParentClass";
    RegisterClassA(&cls);
}