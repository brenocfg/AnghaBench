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
struct string_enumerator {int num_resets; int num_expand; char* last_expand; } ;
typedef  char WCHAR ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_CHAR ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  dispatch_messages () ; 
 scalar_t__ lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_aclist_expand(HWND hwnd_edit, void *enumerator)
{
    struct string_enumerator *obj = (struct string_enumerator*)enumerator;
    static WCHAR str1[] = {'t','e','s','t',0};
    static WCHAR str1a[] = {'t','e','s','t','\\',0};
    static WCHAR str2[] = {'t','e','s','t','\\','f','o','o','\\','b','a','r','\\','b','a',0};
    static WCHAR str2a[] = {'t','e','s','t','\\','f','o','o','\\','b','a','r','\\',0};
    static WCHAR str2b[] = {'t','e','s','t','\\','f','o','o','\\','b','a','r','\\','b','a','z','_','b','b','q','\\',0};
    obj->num_resets = 0;

    ok(obj->num_expand == 0, "Expected 0 expansions, got %u\n", obj->num_expand);
    SendMessageW(hwnd_edit, WM_SETTEXT, 0, (LPARAM)str1);
    SendMessageW(hwnd_edit, EM_SETSEL, ARRAY_SIZE(str1) - 1, ARRAY_SIZE(str1) - 1);
    SendMessageW(hwnd_edit, WM_CHAR, '\\', 1);
    dispatch_messages();
    ok(obj->num_expand == 1, "Expected 1 expansion, got %u\n", obj->num_expand);
    ok(lstrcmpW(obj->last_expand, str1a) == 0, "Expected %s, got %s\n", wine_dbgstr_w(str1a), wine_dbgstr_w(obj->last_expand));
    ok(obj->num_resets == 1, "Expected 1 reset, got %u\n", obj->num_resets);
    SendMessageW(hwnd_edit, WM_SETTEXT, 0, (LPARAM)str2);
    SendMessageW(hwnd_edit, EM_SETSEL, ARRAY_SIZE(str2) - 1, ARRAY_SIZE(str2) - 1);
    SendMessageW(hwnd_edit, WM_CHAR, 'z', 1);
    dispatch_messages();
    ok(obj->num_expand == 2, "Expected 2 expansions, got %u\n", obj->num_expand);
    ok(lstrcmpW(obj->last_expand, str2a) == 0, "Expected %s, got %s\n", wine_dbgstr_w(str2a), wine_dbgstr_w(obj->last_expand));
    ok(obj->num_resets == 2, "Expected 2 resets, got %u\n", obj->num_resets);
    SetFocus(hwnd_edit);
    SendMessageW(hwnd_edit, WM_CHAR, '_', 1);
    SendMessageW(hwnd_edit, WM_CHAR, 'b', 1);
    SetFocus(0);
    SetFocus(hwnd_edit);
    SendMessageW(hwnd_edit, WM_CHAR, 'b', 1);
    SendMessageW(hwnd_edit, WM_CHAR, 'q', 1);
    dispatch_messages();
    ok(obj->num_expand == 2, "Expected 2 expansions, got %u\n", obj->num_expand);
    ok(obj->num_resets == 2, "Expected 2 resets, got %u\n", obj->num_resets);
    SendMessageW(hwnd_edit, WM_CHAR, '\\', 1);
    dispatch_messages();
    ok(obj->num_expand == 3, "Expected 3 expansions, got %u\n", obj->num_expand);
    ok(lstrcmpW(obj->last_expand, str2b) == 0, "Expected %s, got %s\n", wine_dbgstr_w(str2b), wine_dbgstr_w(obj->last_expand));
    ok(obj->num_resets == 3, "Expected 3 resets, got %u\n", obj->num_resets);
    SendMessageW(hwnd_edit, EM_SETSEL, ARRAY_SIZE(str1a) - 1, -1);
    SendMessageW(hwnd_edit, WM_CHAR, 'x', 1);
    SendMessageW(hwnd_edit, WM_CHAR, 'y', 1);
    dispatch_messages();
    ok(obj->num_expand == 4, "Expected 4 expansions, got %u\n", obj->num_expand);
    ok(lstrcmpW(obj->last_expand, str1a) == 0, "Expected %s, got %s\n", wine_dbgstr_w(str1a), wine_dbgstr_w(obj->last_expand));
    ok(obj->num_resets == 4, "Expected 4 resets, got %u\n", obj->num_resets);
    SendMessageW(hwnd_edit, EM_SETSEL, ARRAY_SIZE(str1) - 1, -1);
    SendMessageW(hwnd_edit, WM_CHAR, 'x', 1);
    dispatch_messages();
    ok(obj->num_expand == 4, "Expected 4 expansions, got %u\n", obj->num_expand);
    ok(obj->num_resets == 5, "Expected 5 resets, got %u\n", obj->num_resets);
}