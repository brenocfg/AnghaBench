#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* cy; void* cx; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {TYPE_6__ extent; TYPE_5__ IOleCommandTarget_iface; TYPE_4__ IOleInPlaceActiveObject_iface; TYPE_3__ IOleControl_iface; TYPE_2__ IOleInPlaceObject_iface; TYPE_1__ IOleObject_iface; } ;
typedef  TYPE_7__ WebBrowser ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 void* MulDiv (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OleCommandTargetVtbl ; 
 int /*<<< orphan*/  OleControlVtbl ; 
 int /*<<< orphan*/  OleInPlaceActiveObjectVtbl ; 
 int /*<<< orphan*/  OleInPlaceObjectVtbl ; 
 int /*<<< orphan*/  OleObjectVtbl ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void WebBrowser_OleObject_Init(WebBrowser *This)
{
    DWORD dpi_x;
    DWORD dpi_y;
    HDC hdc;

    /* default aspect ratio is 96dpi / 96dpi */
    hdc = GetDC(0);
    dpi_x = GetDeviceCaps(hdc, LOGPIXELSX);
    dpi_y = GetDeviceCaps(hdc, LOGPIXELSY);
    ReleaseDC(0, hdc);

    This->IOleObject_iface.lpVtbl              = &OleObjectVtbl;
    This->IOleInPlaceObject_iface.lpVtbl       = &OleInPlaceObjectVtbl;
    This->IOleControl_iface.lpVtbl             = &OleControlVtbl;
    This->IOleInPlaceActiveObject_iface.lpVtbl = &OleInPlaceActiveObjectVtbl;
    This->IOleCommandTarget_iface.lpVtbl       = &OleCommandTargetVtbl;

    /* Default size is 50x20 pixels, in himetric units */
    This->extent.cx = MulDiv( 50, 2540, dpi_x );
    This->extent.cy = MulDiv( 20, 2540, dpi_y );
}