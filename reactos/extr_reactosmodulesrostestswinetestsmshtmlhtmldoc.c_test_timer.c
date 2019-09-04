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
typedef  int /*<<< orphan*/  MSG ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 int EXPECT_SETTITLE ; 
 int EXPECT_UPDATEUI ; 
 int /*<<< orphan*/  Exec_SETTITLE ; 
 int /*<<< orphan*/  Exec_UPDATECOMMANDS ; 
 scalar_t__ GetMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateUI ; 
 int /*<<< orphan*/  called_Exec_SETTITLE ; 
 int /*<<< orphan*/  called_UpdateUI ; 
 int /*<<< orphan*/  doc_hwnd ; 

__attribute__((used)) static void test_timer(DWORD flags)
{
    BOOL *b = &called_Exec_SETTITLE;
    MSG msg;

    if(flags & EXPECT_UPDATEUI) {
        SET_EXPECT(UpdateUI);
        SET_EXPECT(Exec_UPDATECOMMANDS);
        b = &called_UpdateUI;
    }
    if(flags & EXPECT_SETTITLE)
        SET_EXPECT(Exec_SETTITLE);

    while(!*b && GetMessageA(&msg, doc_hwnd, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    if(flags & EXPECT_UPDATEUI) {
        CHECK_CALLED(UpdateUI);
        CHECK_CALLED(Exec_UPDATECOMMANDS);
    }
    if(flags & EXPECT_SETTITLE)
        CHECK_CALLED(Exec_SETTITLE);
}