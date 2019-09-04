#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_name ;
typedef  int /*<<< orphan*/  mbi ;
struct TYPE_7__ {int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSW ;
struct TYPE_8__ {int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_2__ WNDCLASSA ;
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  AllocationBase; } ;
typedef  int SIZE_T ;
typedef  TYPE_3__ MEMORY_BASIC_INFORMATION ;
typedef  int BOOL ;

/* Variables and functions */
 int GetClassInfoA (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int GetClassInfoW (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 char* GetLastError () ; 
 int GetModuleFileNameA (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetProcAddress (scalar_t__,char*) ; 
 int MAX_PATH ; 
 int VirtualQuery (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_IME(void)
{
    static const WCHAR ime_classW[] = {'I','M','E',0};

    char module_name[MAX_PATH], *ptr;
    MEMORY_BASIC_INFORMATION mbi;
    WNDCLASSW wnd_classw;
    WNDCLASSA wnd_class;
    SIZE_T size;
    BOOL ret;

    if (!GetProcAddress(GetModuleHandleA("user32.dll"), "BroadcastSystemMessageExA"))
    {
        win_skip("BroadcastSystemMessageExA not available, skipping IME class test\n");
        return;
    }

    ok(GetModuleHandleA("imm32") != 0, "imm32.dll is not loaded\n");

    ret = GetClassInfoA(NULL, "IME", &wnd_class);
    ok(ret, "GetClassInfo failed: %d\n", GetLastError());

    size = VirtualQuery(wnd_class.lpfnWndProc, &mbi, sizeof(mbi));
    ok(size == sizeof(mbi), "VirtualQuery returned %ld\n", size);
    if (size == sizeof(mbi)) {
        size = GetModuleFileNameA(mbi.AllocationBase, module_name, sizeof(module_name));
        ok(size, "GetModuleFileName failed\n");
        for (ptr = module_name+size-1; ptr > module_name; ptr--)
            if (*ptr == '\\' || *ptr == '/') break;
        if (*ptr == '\\' || *ptr=='/') ptr++;
        ok(!lstrcmpiA(ptr, "user32.dll") || !lstrcmpiA(ptr, "ntdll.dll"), "IME window proc implemented in %s\n", ptr);
    }

    ret = GetClassInfoW(NULL, ime_classW, &wnd_classw);
    ok(ret, "GetClassInfo failed: %d\n", GetLastError());

    size = VirtualQuery(wnd_classw.lpfnWndProc, &mbi, sizeof(mbi));
    ok(size == sizeof(mbi), "VirtualQuery returned %ld\n", size);
    size = GetModuleFileNameA(mbi.AllocationBase, module_name, sizeof(module_name));
    ok(size, "GetModuleFileName failed\n");
    for (ptr = module_name+size-1; ptr > module_name; ptr--)
        if (*ptr == '\\' || *ptr == '/') break;
    if (*ptr == '\\' || *ptr=='/') ptr++;
    ok(!lstrcmpiA(ptr, "user32.dll") || !lstrcmpiA(ptr, "ntdll.dll"), "IME window proc implemented in %s\n", ptr);
}