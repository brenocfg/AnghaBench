#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ps; } ;
typedef  TYPE_2__ ps_struct_t ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int /*<<< orphan*/  hWndOwner; } ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  IDD_PASTESPECIAL ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oleui_msg_help ; 

__attribute__((used)) static void post_help_msg(HWND hdlg, ps_struct_t *ps_struct)
{
    PostMessageW(ps_struct->ps->hWndOwner, oleui_msg_help, (WPARAM)hdlg, IDD_PASTESPECIAL);
}