#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cbSize; int /*<<< orphan*/  wAlignment; int /*<<< orphan*/  dwMask; } ;
struct TYPE_10__ {int style; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_2__ ITextHost_iface; TYPE_4__ para_fmt; int /*<<< orphan*/  bEmulateVersion10; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ ITextHostImpl ;
typedef  TYPE_2__ ITextHost ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ CREATESTRUCTW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_1__* CoTaskMemAlloc (int) ; 
 int ES_CENTER ; 
 int ES_RIGHT ; 
 int /*<<< orphan*/  PFA_CENTER ; 
 int /*<<< orphan*/  PFA_LEFT ; 
 int /*<<< orphan*/  PFA_RIGHT ; 
 int /*<<< orphan*/  PFM_ALIGNMENT ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  textHostVtbl ; 

ITextHost *ME_CreateTextHost(HWND hwnd, CREATESTRUCTW *cs, BOOL bEmulateVersion10)
{
    ITextHostImpl *texthost;

    texthost = CoTaskMemAlloc(sizeof(*texthost));
    if (!texthost) return NULL;

    texthost->ITextHost_iface.lpVtbl = &textHostVtbl;
    texthost->ref = 1;
    texthost->hWnd = hwnd;
    texthost->bEmulateVersion10 = bEmulateVersion10;
    memset( &texthost->para_fmt, 0, sizeof(texthost->para_fmt) );
    texthost->para_fmt.cbSize = sizeof(texthost->para_fmt);
    texthost->para_fmt.dwMask = PFM_ALIGNMENT;
    texthost->para_fmt.wAlignment = PFA_LEFT;
    if (cs->style & ES_RIGHT)
        texthost->para_fmt.wAlignment = PFA_RIGHT;
    if (cs->style & ES_CENTER)
        texthost->para_fmt.wAlignment = PFA_CENTER;

    return &texthost->ITextHost_iface;
}