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
struct TYPE_4__ {int mode; int wndExtX; int wndExtY; int vportExtX; int vportExtY; } ;
struct TYPE_5__ {TYPE_1__ state; } ;
typedef  TYPE_2__ enum_emh_data ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  HORZSIZE ; 
#define  MM_ANISOTROPIC 135 
#define  MM_HIENGLISH 134 
#define  MM_HIMETRIC 133 
#define  MM_ISOTROPIC 132 
#define  MM_LOENGLISH 131 
#define  MM_LOMETRIC 130 
#define  MM_TEXT 129 
#define  MM_TWIPS 128 
 void* MulDiv (int,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  VERTRES ; 
 int /*<<< orphan*/  VERTSIZE ; 

__attribute__((used)) static void EMF_SetMapMode(HDC hdc, enum_emh_data *info)
{
    INT horzSize = GetDeviceCaps( hdc, HORZSIZE );
    INT vertSize = GetDeviceCaps( hdc, VERTSIZE );
    INT horzRes  = GetDeviceCaps( hdc, HORZRES );
    INT vertRes  = GetDeviceCaps( hdc, VERTRES );

    TRACE("%d\n", info->state.mode);

    switch(info->state.mode)
    {
    case MM_TEXT:
        info->state.wndExtX   = 1;
        info->state.wndExtY   = 1;
        info->state.vportExtX = 1;
        info->state.vportExtY = 1;
        break;
    case MM_LOMETRIC:
    case MM_ISOTROPIC:
        info->state.wndExtX   = horzSize * 10;
        info->state.wndExtY   = vertSize * 10;
        info->state.vportExtX = horzRes;
        info->state.vportExtY = -vertRes;
        break;
    case MM_HIMETRIC:
        info->state.wndExtX   = horzSize * 100;
        info->state.wndExtY   = vertSize * 100;
        info->state.vportExtX = horzRes;
        info->state.vportExtY = -vertRes;
        break;
    case MM_LOENGLISH:
        info->state.wndExtX   = MulDiv(1000, horzSize, 254);
        info->state.wndExtY   = MulDiv(1000, vertSize, 254);
        info->state.vportExtX = horzRes;
        info->state.vportExtY = -vertRes;
        break;
    case MM_HIENGLISH:
        info->state.wndExtX   = MulDiv(10000, horzSize, 254);
        info->state.wndExtY   = MulDiv(10000, vertSize, 254);
        info->state.vportExtX = horzRes;
        info->state.vportExtY = -vertRes;
        break;
    case MM_TWIPS:
        info->state.wndExtX   = MulDiv(14400, horzSize, 254);
        info->state.wndExtY   = MulDiv(14400, vertSize, 254);
        info->state.vportExtX = horzRes;
        info->state.vportExtY = -vertRes;
        break;
    case MM_ANISOTROPIC:
        break;
    default:
        return;
    }
}