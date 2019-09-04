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
struct TYPE_4__ {scalar_t__ hwnd; } ;
struct TYPE_5__ {TYPE_1__ doc_host; } ;
typedef  TYPE_2__ WebBrowser ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT resize_window(WebBrowser *This, LONG width, LONG height)
{
    if(This->doc_host.hwnd)
        SetWindowPos(This->doc_host.hwnd, NULL, 0, 0, width, height,
                     SWP_NOZORDER | SWP_NOACTIVATE);

    return 0;
}