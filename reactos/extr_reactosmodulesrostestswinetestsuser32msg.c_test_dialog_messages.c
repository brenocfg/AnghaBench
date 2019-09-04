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
struct TYPE_4__ {char* lpszClassName; int /*<<< orphan*/  hInstance; int /*<<< orphan*/ * lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int LRESULT ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDialogParamA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DefDlgProcA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DialogBoxA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_GETSEL ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetClassInfoA (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetFocus () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HIWORD (int) ; 
 int IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int) ; 
 int MAKELRESULT (int /*<<< orphan*/ ,int) ; 
 int RegisterClassA (TYPE_1__*) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TestModalDlgProc2 ; 
 int /*<<< orphan*/  UnregisterClassA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETFOCUS ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int WS_BORDER ; 
 int WS_CAPTION ; 
 int WS_CHILD ; 
 int WS_DLGFRAME ; 
 int /*<<< orphan*/  WS_EX_DLGMODALFRAME ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_SYSMENU ; 
 int WS_TABSTOP ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WmCreateDialogParamSeq_0 ; 
 int /*<<< orphan*/  WmCreateDialogParamSeq_1 ; 
 int /*<<< orphan*/  WmCreateDialogParamSeq_2 ; 
 int /*<<< orphan*/  WmCreateDialogParamSeq_3 ; 
 int /*<<< orphan*/  WmCreateDialogParamSeq_4 ; 
 int /*<<< orphan*/  WmDefDlgSetFocus_1 ; 
 int /*<<< orphan*/  WmDefDlgSetFocus_2 ; 
 int /*<<< orphan*/  WmModalDialogSeq_2 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subclass_edit () ; 
 int /*<<< orphan*/ * test_dlg_proc ; 
 int /*<<< orphan*/ * test_dlg_proc2 ; 
 int /*<<< orphan*/ * test_dlg_proc3 ; 
 int /*<<< orphan*/ * test_dlg_proc4 ; 

__attribute__((used)) static void test_dialog_messages(void)
{
    WNDCLASSA cls;
    HWND hdlg, hedit1, hedit2, hfocus, parent, child, child2;
    LRESULT ret;

#define set_selection(hctl, start, end) \
    ret = SendMessageA(hctl, EM_SETSEL, start, end); \
    ok(ret == 1, "EM_SETSEL returned %ld\n", ret);

#define check_selection(hctl, start, end) \
    ret = SendMessageA(hctl, EM_GETSEL, 0, 0); \
    ok(ret == MAKELRESULT(start, end), "wrong selection (%d - %d)\n", LOWORD(ret), HIWORD(ret));

    subclass_edit();

    hdlg = CreateWindowExA(WS_EX_DLGMODALFRAME, "TestDialogClass", NULL,
                          WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_DLGFRAME,
                          0, 0, 100, 100, 0, 0, 0, NULL);
    ok(hdlg != 0, "Failed to create custom dialog window\n");

    hedit1 = CreateWindowExA(0, "my_edit_class", NULL,
                           WS_CHILD|WS_BORDER|WS_VISIBLE|WS_TABSTOP,
                           0, 0, 80, 20, hdlg, (HMENU)1, 0, NULL);
    ok(hedit1 != 0, "Failed to create edit control\n");
    hedit2 = CreateWindowExA(0, "my_edit_class", NULL,
                           WS_CHILD|WS_BORDER|WS_VISIBLE|WS_TABSTOP,
                           0, 40, 80, 20, hdlg, (HMENU)2, 0, NULL);
    ok(hedit2 != 0, "Failed to create edit control\n");

    SendMessageA(hedit1, WM_SETTEXT, 0, (LPARAM)"hello");
    SendMessageA(hedit2, WM_SETTEXT, 0, (LPARAM)"bye");

    hfocus = GetFocus();
    ok(hfocus == hdlg, "wrong focus %p\n", hfocus);

    SetFocus(hedit2);
    hfocus = GetFocus();
    ok(hfocus == hedit2, "wrong focus %p\n", hfocus);

    check_selection(hedit1, 0, 0);
    check_selection(hedit2, 0, 0);

    set_selection(hedit2, 0, -1);
    check_selection(hedit2, 0, 3);

    SetFocus(0);
    hfocus = GetFocus();
    ok(hfocus == 0, "wrong focus %p\n", hfocus);

    flush_sequence();
    ret = DefDlgProcA(hdlg, WM_SETFOCUS, 0, 0);
    ok(ret == 0, "WM_SETFOCUS returned %ld\n", ret);
    ok_sequence(WmDefDlgSetFocus_1, "DefDlgProc(WM_SETFOCUS) 1", FALSE);

    hfocus = GetFocus();
    ok(hfocus == hedit1, "wrong focus %p\n", hfocus);

    check_selection(hedit1, 0, 5);
    check_selection(hedit2, 0, 3);

    flush_sequence();
    ret = DefDlgProcA(hdlg, WM_SETFOCUS, 0, 0);
    ok(ret == 0, "WM_SETFOCUS returned %ld\n", ret);
    ok_sequence(WmDefDlgSetFocus_2, "DefDlgProc(WM_SETFOCUS) 2", FALSE);

    hfocus = GetFocus();
    ok(hfocus == hedit1, "wrong focus %p\n", hfocus);

    check_selection(hedit1, 0, 5);
    check_selection(hedit2, 0, 3);

    EndDialog(hdlg, 0);
    DestroyWindow(hedit1);
    DestroyWindow(hedit2);
    DestroyWindow(hdlg);
    flush_sequence();

#undef set_selection
#undef check_selection

    ok(GetClassInfoA(0, "#32770", &cls), "GetClassInfo failed\n");
    cls.lpszClassName = "MyDialogClass";
    cls.hInstance = GetModuleHandleA(NULL);
    /* need a cast since a dlgproc is used as a wndproc */
    cls.lpfnWndProc = test_dlg_proc;
    if (!RegisterClassA(&cls)) assert(0);

    SetFocus(0);
    flush_sequence();
    hdlg = CreateDialogParamA(0, "CLASS_TEST_DIALOG_2", 0, test_dlg_proc, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    ok_sequence(WmCreateDialogParamSeq_0, "CreateDialogParam_0", FALSE);
    hfocus = GetFocus();
    ok(hfocus == 0, "wrong focus %p\n", hfocus);
    EndDialog(hdlg, 0);
    DestroyWindow(hdlg);
    flush_sequence();

    SetFocus(0);
    flush_sequence();
    hdlg = CreateDialogParamA(0, "CLASS_TEST_DIALOG_2", 0, test_dlg_proc, 1);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    ok_sequence(WmCreateDialogParamSeq_1, "CreateDialogParam_1", FALSE);
    hfocus = GetFocus();
    ok(hfocus == hdlg, "wrong focus %p\n", hfocus);
    EndDialog(hdlg, 0);
    DestroyWindow(hdlg);
    flush_sequence();

    hdlg = CreateDialogParamA(0, "CLASS_TEST_DIALOG_2", 0, NULL, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    ok_sequence(WmCreateDialogParamSeq_2, "CreateDialogParam_2", FALSE);
    EndDialog(hdlg, 0);
    DestroyWindow(hdlg);
    flush_sequence();

    hdlg = CreateDialogParamA(0, "FOCUS_TEST_DIALOG_3", 0, test_dlg_proc2, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    ok_sequence(WmCreateDialogParamSeq_3, "CreateDialogParam_3", TRUE);
    EndDialog(hdlg, 0);
    DestroyWindow(hdlg);
    flush_sequence();

    UnregisterClassA( cls.lpszClassName, cls.hInstance );
    cls.lpfnWndProc = test_dlg_proc4;
    ok( RegisterClassA(&cls), "failed to register class again\n" );
    hdlg = CreateDialogParamA(0, "FOCUS_TEST_DIALOG_4", 0, test_dlg_proc3, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    ok_sequence(WmCreateDialogParamSeq_4, "CreateDialogParam_4", TRUE);
    EndDialog(hdlg, 0);
    DestroyWindow(hdlg);
    flush_sequence();

    UnregisterClassA(cls.lpszClassName, cls.hInstance);

    parent = CreateWindowExA(0, "TestParentClass", "Test parent",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             100, 100, 200, 200, 0, 0, 0, NULL);
    ok (parent != 0, "Failed to create parent window\n");

    /* This child has no parent set. We will later call SetParent on it,
     * so that it will have a parent set, but no WS_CHILD style. */
    child = CreateWindowExA(0, "TestWindowClass", "Test child",
                            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                            100, 100, 200, 200, 0, 0, 0, NULL);
    ok (child != 0, "Failed to create child window\n");

    /* This is a regular child window. When used as an owner, the other
     * child window will be used. */
    child2 = CreateWindowExA(0, "SimpleWindowClass", "Test child2",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
                             100, 100, 200, 200, child, 0, 0, NULL);
    ok (child2 != 0, "Failed to create child window\n");

    SetParent(child, parent);
    SetFocus(child);

    flush_sequence();
    DialogBoxA( 0, "TEST_DIALOG", child2, TestModalDlgProc2 );
    ok_sequence(WmModalDialogSeq_2, "ModalDialog2", TRUE);

    DestroyWindow(child2);
    DestroyWindow(child);
    DestroyWindow(parent);
    flush_sequence();
}