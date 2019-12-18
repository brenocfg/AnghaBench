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
typedef  int /*<<< orphan*/  lf ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int lfHeight; } ;
typedef  TYPE_1__ LOGFONTA ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateFontIndirectA (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_CD_SEQ_INDEX ; 
 int /*<<< orphan*/  SPI_GETICONTITLELOGFONT ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TVE_EXPAND ; 
 int /*<<< orphan*/  TVM_EXPAND ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_treeview_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_customdraw_font ; 
 scalar_t__ hRoot ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_cd_seq ; 
 int /*<<< orphan*/  sequences ; 

__attribute__((used)) static void test_customdraw(void)
{
    LOGFONTA lf;
    HWND hwnd;

    hwnd = create_treeview_control(0);
    fill_tree(hwnd);
    SendMessageA(hwnd, TVM_EXPAND, TVE_EXPAND, (WPARAM)hRoot);

    /* create additional font, custom draw handler will select it */
    SystemParametersInfoA(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
    lf.lfHeight *= 2;
    g_customdraw_font = CreateFontIndirectA(&lf);
    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    InvalidateRect(hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
    ok_sequence(sequences, PARENT_CD_SEQ_INDEX, parent_cd_seq, "custom draw notifications", FALSE);
    DeleteObject(g_customdraw_font);
    g_customdraw_font = NULL;

    DestroyWindow(hwnd);
}