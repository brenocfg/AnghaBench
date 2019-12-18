#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cls ;
struct TYPE_4__ {int cbSize; char* lpszClassName; void* lpfnWndProc; void* hInstance; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ WNDCLASSEXA ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CS_CLASSDC ; 
 int /*<<< orphan*/  CS_OWNDC ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* DefWindowProcA ; 
 int DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 scalar_t__ GetDC (scalar_t__) ; 
 scalar_t__ GetDesktopWindow () ; 
 void* GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int GetObjectType (scalar_t__) ; 
 scalar_t__ GetWindowDC (scalar_t__) ; 
 int OBJ_DC ; 
 int RegisterClassExA (TYPE_1__*) ; 
 int ReleaseDC (scalar_t__,scalar_t__) ; 
 int UnregisterClassA (char*,void*) ; 
 int WS_POPUP ; 
 int WS_VISIBLE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_DeleteDC(void)
{
    HWND hwnd;
    HDC hdc, hdc_test;
    WNDCLASSEXA cls;
    int ret;

    /* window DC */
    hwnd = CreateWindowExA(0, "static", NULL, WS_POPUP|WS_VISIBLE, 0,0,100,100,
                           0, 0, 0, NULL);
    ok(hwnd != 0, "CreateWindowExA failed\n");

    hdc = GetDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(!ret || broken(ret) /* win9x */, "GetObjectType should fail for a deleted DC\n");

    hdc = GetWindowDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(!ret || broken(ret) /* win9x */, "GetObjectType should fail for a deleted DC\n");

    DestroyWindow(hwnd);

    /* desktop window DC */
    hwnd = GetDesktopWindow();
    ok(hwnd != 0, "GetDesktopWindow failed\n");

    hdc = GetDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(!ret || broken(ret) /* win9x */, "GetObjectType should fail for a deleted DC\n");

    hdc = GetWindowDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(!ret || broken(ret) /* win9x */, "GetObjectType should fail for a deleted DC\n");

    /* CS_CLASSDC */
    memset(&cls, 0, sizeof(cls));
    cls.cbSize = sizeof(cls);
    cls.style = CS_CLASSDC;
    cls.hInstance = GetModuleHandleA(NULL);
    cls.lpszClassName = "Wine class DC";
    cls.lpfnWndProc = DefWindowProcA;
    ret = RegisterClassExA(&cls);
    ok(ret, "RegisterClassExA failed\n");

    hwnd = CreateWindowExA(0, "Wine class DC", NULL, WS_POPUP|WS_VISIBLE, 0,0,100,100,
                           0, 0, 0, NULL);
    ok(hwnd != 0, "CreateWindowExA failed\n");

    hdc = GetDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = ReleaseDC(hwnd, hdc);
    ok(ret, "ReleaseDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);

    hdc_test = hdc;

    hdc = GetWindowDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(!ret || broken(ret) /* win9x */, "GetObjectType should fail for a deleted DC\n");

    DestroyWindow(hwnd);

    ret = GetObjectType(hdc_test);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);

    ret = UnregisterClassA("Wine class DC", GetModuleHandleA(NULL));
    ok(ret, "UnregisterClassA failed\n");

    ret = GetObjectType(hdc_test);
    ok(!ret, "GetObjectType should fail for a deleted DC\n");

    /* CS_OWNDC */
    memset(&cls, 0, sizeof(cls));
    cls.cbSize = sizeof(cls);
    cls.style = CS_OWNDC;
    cls.hInstance = GetModuleHandleA(NULL);
    cls.lpszClassName = "Wine own DC";
    cls.lpfnWndProc = DefWindowProcA;
    ret = RegisterClassExA(&cls);
    ok(ret, "RegisterClassExA failed\n");

    hwnd = CreateWindowExA(0, "Wine own DC", NULL, WS_POPUP|WS_VISIBLE, 0,0,100,100,
                           0, 0, 0, NULL);
    ok(hwnd != 0, "CreateWindowExA failed\n");

    hdc = GetDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = ReleaseDC(hwnd, hdc);
    ok(ret, "ReleaseDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);

    hdc = GetWindowDC(hwnd);
    ok(hdc != 0, "GetDC failed\n");
    ret = GetObjectType(hdc);
    ok(ret == OBJ_DC, "expected OBJ_DC, got %d\n", ret);
    ret = DeleteDC(hdc);
    ok(ret, "DeleteDC failed\n");
    ret = GetObjectType(hdc);
    ok(!ret || broken(ret) /* win9x */, "GetObjectType should fail for a deleted DC\n");

    DestroyWindow(hwnd);

    ret = UnregisterClassA("Wine own DC", GetModuleHandleA(NULL));
    ok(ret, "UnregisterClassA failed\n");
}