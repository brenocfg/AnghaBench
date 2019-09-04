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
struct TYPE_3__ {scalar_t__ counter; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ install_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_AXINSTALL_INSTALL ; 
 int /*<<< orphan*/  IDS_AXINSTALL_INSTALLN ; 
 int /*<<< orphan*/  ID_AXINSTALL_INSTALL_BTN ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  urlmon_instance ; 

__attribute__((used)) static void update_counter(install_ctx_t *ctx, HWND hwnd)
{
    WCHAR text[100];

    if(--ctx->counter <= 0) {
        HWND button_hwnd;

        KillTimer(hwnd, ctx->timer);
        LoadStringW(urlmon_instance, IDS_AXINSTALL_INSTALL, text, ARRAY_SIZE(text));

        button_hwnd = GetDlgItem(hwnd, ID_AXINSTALL_INSTALL_BTN);
        EnableWindow(button_hwnd, TRUE);
    }else {
        WCHAR buf[100];
        LoadStringW(urlmon_instance, IDS_AXINSTALL_INSTALLN, buf, ARRAY_SIZE(buf));
        sprintfW(text, buf, ctx->counter);
    }

    SetDlgItemTextW(hwnd, ID_AXINSTALL_INSTALL_BTN, text);
}