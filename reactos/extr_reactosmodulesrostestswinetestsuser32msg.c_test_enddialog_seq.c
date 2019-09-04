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
struct message {int member_1; int member_2; int /*<<< orphan*/  member_0; int /*<<< orphan*/  member_3; } ;
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCBT_ACTIVATE ; 
 int /*<<< orphan*/  HCBT_SETFOCUS ; 
 int SWP_HIDEWINDOW ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int WA_ACTIVE ; 
 int WA_INACTIVE ; 
 int /*<<< orphan*/  WM_ACTIVATE ; 
 int /*<<< orphan*/  WM_ENABLE ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  WM_KILLFOCUS ; 
 int /*<<< orphan*/  WM_NCACTIVATE ; 
 int /*<<< orphan*/  WM_QUERYNEWPALETTE ; 
 int /*<<< orphan*/  WM_SETFOCUS ; 
 int /*<<< orphan*/  WM_WINDOWPOSCHANGING ; 
 int defwinproc ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int hook ; 
 int lparam ; 
 int /*<<< orphan*/  ok_sequence (struct message const*,char*,int /*<<< orphan*/ ) ; 
 int optional ; 
 int sent ; 
 int wparam ; 

__attribute__((used)) static void test_enddialog_seq(HWND dialog, HWND owner)
{
    const struct message seq[] = {
        { WM_ENABLE, sent },
        { WM_WINDOWPOSCHANGING, sent|wparam, SWP_HIDEWINDOW|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE },
        { HCBT_ACTIVATE, hook|wparam, (WPARAM)owner },
        { WM_NCACTIVATE, sent|wparam|lparam, WA_INACTIVE, (LPARAM)owner },
        { WM_ACTIVATE, sent|wparam|lparam, WA_INACTIVE, (LPARAM)owner },
        /* FIXME: Following two are optional because Wine sends WM_QUERYNEWPALETTE instead of WM_WINDOWPOSCHANGING */
        { WM_WINDOWPOSCHANGING, sent|wparam|optional, SWP_NOSIZE|SWP_NOMOVE },
        { WM_QUERYNEWPALETTE, sent|optional },
        { WM_NCACTIVATE, sent|wparam|lparam, WA_ACTIVE, (LPARAM)dialog },
        { WM_GETTEXT, sent|optional|defwinproc },
        { WM_ACTIVATE, sent|wparam|lparam, WA_ACTIVE, (LPARAM)dialog },
        { HCBT_SETFOCUS, hook|wparam, (WPARAM)owner },
        { WM_KILLFOCUS, sent|wparam, (WPARAM)owner },
        { WM_SETFOCUS, sent|defwinproc|wparam, (WPARAM)dialog },
        { 0 }
    };

    flush_sequence();
    EndDialog(dialog, 0);
    ok_sequence(seq, "EndDialog", FALSE);
}