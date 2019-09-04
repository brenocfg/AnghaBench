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
struct TYPE_4__ {char* lpszClassName; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ CreateDialogParamA (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  EnableWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndDialog (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetActiveWindow () ; 
 int /*<<< orphan*/  GetClassInfoA (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 scalar_t__ GetForegroundWindow () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  IsWindowEnabled (scalar_t__) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  SetForegroundWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetParent (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetWindowLongW (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnregisterClassA (char*,int /*<<< orphan*/ ) ; 
 int WS_CAPTION ; 
 int WS_CHILD ; 
 int WS_DISABLED ; 
 int WS_DLGFRAME ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_POPUP ; 
 int WS_SYSMENU ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_dlg_proc ; 
 int /*<<< orphan*/  test_enddialog_seq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_enddialog_seq2 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_EndDialog(void)
{
    HWND hparent, hother, hactive, hdlg, hchild;
    WNDCLASSA cls;

    hparent = CreateWindowExA(0, "TestParentClass", "Test parent",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_DISABLED,
                              100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hparent != 0, "Failed to create parent window\n");

    hother = CreateWindowExA(0, "TestParentClass", "Test parent 2",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                              200, 100, 200, 200, 0, 0, 0, NULL);
    ok (hother != 0, "Failed to create parent window\n");

    ok(GetClassInfoA(0, "#32770", &cls), "GetClassInfo failed\n");
    cls.lpszClassName = "MyDialogClass";
    cls.hInstance = GetModuleHandleA(NULL);
    cls.lpfnWndProc = test_dlg_proc;
    if (!RegisterClassA(&cls)) assert(0);

    flush_sequence();
    SetForegroundWindow(hother);
    hactive = GetForegroundWindow();
    ok(hother == hactive, "Wrong window has focus (%p != %p)\n", hother, hactive);

    /* create a dialog where the parent is disabled, this parent should be
     * enabled and receive focus when dialog exits */
    hdlg = CreateDialogParamA(0, "CLASS_TEST_DIALOG_2", hparent, test_dlg_proc, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    SetForegroundWindow(hdlg);
    hactive = GetForegroundWindow();
    ok(hdlg == hactive, "Wrong window has focus (%p != %p)\n", hdlg, hactive);
    EndDialog(hdlg, 0);
    ok(IsWindowEnabled(hparent), "parent is not enabled\n");
    hactive = GetForegroundWindow();
    ok(hparent == hactive, "Wrong window has focus (parent != active) (active: %p, parent: %p, dlg: %p, other: %p)\n", hactive, hparent, hdlg, hother);
    DestroyWindow(hdlg);
    flush_sequence();

    /* create a dialog where the parent is disabled and set active window to other window before calling EndDialog */
    EnableWindow(hparent, FALSE);
    hdlg = CreateWindowExA(0, "TestDialogClass", NULL,
                          WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_DLGFRAME,
                          0, 0, 100, 100, hparent, 0, 0, NULL);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");
    flush_sequence();
    SetForegroundWindow(hother);
    flush_sequence();
    hactive = GetForegroundWindow();
    ok(hactive == hother, "Wrong foreground (%p != %p)\n", hactive, hother);
    hactive = GetActiveWindow();
    ok(hactive == hother, "Wrong active window (%p != %p)\n", hactive, hother);
    EndDialog(hdlg, 0);
    ok(IsWindowEnabled(hparent), "parent is not enabled\n");
    hactive = GetForegroundWindow();
    ok(hother == hactive, "Wrong window has focus (other != active) (active: %p, parent: %p, dlg: %p, other: %p)\n", hactive, hparent, hdlg, hother);
    DestroyWindow(hdlg);
    flush_sequence();

    DestroyWindow( hparent );

    hparent = CreateWindowExA(0, "TestParentClass", "Test parent",
                              WS_POPUP | WS_VISIBLE | WS_DISABLED,
                              100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hparent != 0, "Failed to create parent window\n");

    hchild = CreateWindowExA(0, "TestWindowClass", "Test child",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_DISABLED,
                             0, 0, 0, 0, 0, 0, 0, NULL);
    ok (hchild != 0, "Failed to create child window\n");

    SetParent(hchild, hparent);

    flush_sequence();
    SetForegroundWindow(hother);
    hactive = GetForegroundWindow();
    ok(hother == hactive, "Wrong foreground window (%p != %p)\n", hother, hactive);

    hdlg = CreateDialogParamA(0, "CLASS_TEST_DIALOG_2", hchild, test_dlg_proc, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");

    SetForegroundWindow(hdlg);
    test_enddialog_seq(hdlg, hchild);

    hactive = GetForegroundWindow();
    ok(hactive == hchild, "Wrong foreground window (active: %p, parent: %p, dlg: %p, other: %p child: %p)\n", hactive, hparent, hdlg, hother, hchild);

    DestroyWindow(hdlg);

    /* Now set WS_CHILD style flag so that it's a real child and its parent will be dialog's owner. */
    SetWindowLongW(hchild, GWL_STYLE, GetWindowLongW(hchild, GWL_STYLE) | WS_CHILD);

    SetForegroundWindow(hother);
    hactive = GetForegroundWindow();
    ok(hother == hactive, "Wrong foreground window (%p != %p)\n", hother, hactive);

    hdlg = CreateDialogParamA(0, "CLASS_TEST_DIALOG_2", hchild, test_dlg_proc, 0);
    ok(IsWindow(hdlg), "CreateDialogParam failed\n");

    SetForegroundWindow(hdlg);
    test_enddialog_seq2(hdlg, hparent);

    hactive = GetForegroundWindow();
    ok(hactive == hparent, "Wrong foreground window (active: %p, parent: %p, dlg: %p, other: %p child: %p)\n", hactive, hparent, hdlg, hother, hchild);
    DestroyWindow(hdlg);
    DestroyWindow(hchild);
    DestroyWindow(hparent);
    DestroyWindow(hother);
    flush_sequence();

    UnregisterClassA(cls.lpszClassName, cls.hInstance);
}