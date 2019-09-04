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
struct TYPE_3__ {scalar_t__ hfont; } ;
typedef  TYPE_1__ msi_font ;
typedef  int /*<<< orphan*/  msi_dialog ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_dialog_find_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT msi_dialog_set_font( msi_dialog *dialog, HWND hwnd, LPCWSTR name )
{
    msi_font *font;

    font = msi_dialog_find_font( dialog, name );
    if( font )
        SendMessageW( hwnd, WM_SETFONT, (WPARAM) font->hfont, TRUE );
    else
        ERR("No font entry for %s\n", debugstr_w(name));
    return ERROR_SUCCESS;
}