#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int wParam; int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ MSG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int DLGC_HASSETSEL ; 
 int DLGC_WANTALLKEYS ; 
 int DLGC_WANTARROWS ; 
 int DLGC_WANTCHARS ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int ES_AUTOHSCROLL ; 
 int ES_AUTOVSCROLL ; 
 int ES_MULTILINE ; 
 int ES_WANTRETURN ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 
 int WS_VSCROLL ; 
 int /*<<< orphan*/  create_editcontrol (int,int /*<<< orphan*/ ) ; 
 int get_edit_style (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_edit_control_1(void)
{
    HWND hwEdit;
    MSG msMessage;
    int i;
    LONG r;

    msMessage.message = WM_KEYDOWN;

    trace("EDIT: Single line\n");
    hwEdit = create_editcontrol(ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0);
    r = get_edit_style(hwEdit);
    ok(r == (ES_AUTOVSCROLL | ES_AUTOHSCROLL), "Wrong style expected 0xc0 got: 0x%x\n", r);
    for (i = 0; i < 65535; i++)
    {
        msMessage.wParam = i;
        r = SendMessageA(hwEdit, WM_GETDLGCODE, 0, (LPARAM) &msMessage);
        ok(r == (DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTARROWS),
            "Expected DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTARROWS got %x\n", r);
    }
    DestroyWindow(hwEdit);

    trace("EDIT: Single line want returns\n");
    hwEdit = create_editcontrol(ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0);
    r = get_edit_style(hwEdit);
    ok(r == (ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN), "Wrong style expected 0x10c0 got: 0x%x\n", r);
    for (i = 0; i < 65535; i++)
    {
        msMessage.wParam = i;
        r = SendMessageA(hwEdit, WM_GETDLGCODE, 0, (LPARAM) &msMessage);
        ok(r == (DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTARROWS),
            "Expected DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTARROWS got %x\n", r);
    }
    DestroyWindow(hwEdit);

    trace("EDIT: Multiline line\n");
    hwEdit = create_editcontrol(ES_MULTILINE | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0);
    r = get_edit_style(hwEdit);
    ok(r == (ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE), "Wrong style expected 0xc4 got: 0x%x\n", r);
    for (i = 0; i < 65535; i++)
    {
        msMessage.wParam = i;
        r = SendMessageA(hwEdit, WM_GETDLGCODE, 0, (LPARAM) &msMessage);
        ok(r == (DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTALLKEYS | DLGC_WANTARROWS),
            "Expected DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTALLKEYS | DLGC_WANTARROWS got %x\n", r);
    }
    DestroyWindow(hwEdit);

    trace("EDIT: Multi line want returns\n");
    hwEdit = create_editcontrol(ES_MULTILINE | WS_VSCROLL | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0);
    r = get_edit_style(hwEdit);
    ok(r == (ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE), "Wrong style expected 0x10c4 got: 0x%x\n", r);
    for (i = 0; i < 65535; i++)
    {
        msMessage.wParam = i;
        r = SendMessageA(hwEdit, WM_GETDLGCODE, 0, (LPARAM) &msMessage);
        ok(r == (DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTALLKEYS | DLGC_WANTARROWS),
            "Expected DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTALLKEYS | DLGC_WANTARROWS got %x\n", r);
    }
    DestroyWindow(hwEdit);
}