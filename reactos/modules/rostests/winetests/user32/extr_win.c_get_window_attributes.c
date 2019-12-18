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
struct window_attributes {int is_visible; int is_enabled; int is_groupbox; int is_httransparent; int is_extransparent; scalar_t__* class_name; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ BS_GROUPBOX ; 
 scalar_t__ BS_TYPEMASK ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClassNameA (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ GetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HTTRANSPARENT ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NCHITTEST ; 
 scalar_t__ WS_DISABLED ; 
 scalar_t__ WS_EX_TRANSPARENT ; 
 scalar_t__ WS_VISIBLE ; 
 int /*<<< orphan*/  lstrcmpiA (scalar_t__*,char*) ; 

__attribute__((used)) static void get_window_attributes(HWND hwnd, struct window_attributes *attrs)
{
    DWORD style, ex_style, hittest;

    style = GetWindowLongA(hwnd, GWL_STYLE);
    ex_style = GetWindowLongA(hwnd, GWL_EXSTYLE);
    attrs->class_name[0] = 0;
    GetClassNameA(hwnd, attrs->class_name, sizeof(attrs->class_name));
    hittest = SendMessageA(hwnd, WM_NCHITTEST, 0, 0);

    attrs->is_visible = (style & WS_VISIBLE) != 0;
    attrs->is_enabled = (style & WS_DISABLED) == 0;
    attrs->is_groupbox = !lstrcmpiA(attrs->class_name, "Button") && (style & BS_TYPEMASK) == BS_GROUPBOX;
    attrs->is_httransparent = hittest == HTTRANSPARENT;
    attrs->is_extransparent = (ex_style & WS_EX_TRANSPARENT) != 0;
}