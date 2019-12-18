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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__* wnd_class; scalar_t__* wnd_name; int /*<<< orphan*/  msg_hwnd; } ;
typedef  TYPE_1__ SPY_INSTANCE ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  InternalGetWindowText (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  SPY_GetClassName (TYPE_1__*) ; 

__attribute__((used)) static void SPY_GetWndName( SPY_INSTANCE *sp_e )
{
    INT len;

    SPY_GetClassName( sp_e );

    len = InternalGetWindowText(sp_e->msg_hwnd, sp_e->wnd_name, sizeof(sp_e->wnd_name)/sizeof(WCHAR));
    if(!len) /* get class name */
    {
        LPWSTR dst = sp_e->wnd_name;
        LPWSTR src = sp_e->wnd_class;
        int n = sizeof(sp_e->wnd_name)/sizeof(WCHAR) - 3;
        *dst++ = '{';
        while ((n-- > 0) && *src) *dst++ = *src++;
        *dst++ = '}';
        *dst = 0;
    }
}