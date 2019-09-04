#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IOleInPlaceUIWindow_iface; } ;
typedef  TYPE_1__ InPlaceUIWindow ;
typedef  TYPE_2__ IOleInPlaceUIWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  OleInPlaceUIWindowVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* heap_alloc_zero (int) ; 

HRESULT create_ip_window(IOleInPlaceUIWindow **ret)
{
    InPlaceUIWindow *uiwindow;

    uiwindow = heap_alloc_zero(sizeof(*uiwindow));
    if(!uiwindow)
        return E_OUTOFMEMORY;

    uiwindow->IOleInPlaceUIWindow_iface.lpVtbl = &OleInPlaceUIWindowVtbl;
    uiwindow->ref = 1;

    *ret = &uiwindow->IOleInPlaceUIWindow_iface;
    return S_OK;
}