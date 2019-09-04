#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wgl_dc_data {struct sw_framebuffer* sw_data; } ;
struct sw_framebuffer {int height; TYPE_3__* pixel_format; int /*<<< orphan*/  BackBuffer; int /*<<< orphan*/  width; int /*<<< orphan*/  Hdc; TYPE_1__* gl_visual; } ;
struct TYPE_7__ {int biSize; int biBitCount; int biPlanes; int biSizeImage; int biHeight; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biWidth; scalar_t__ biYPelsPerMeter; scalar_t__ biXPelsPerMeter; scalar_t__ biClrUsed; scalar_t__ biClrImportant; } ;
struct TYPE_9__ {int /*<<< orphan*/ * bmiColors; TYPE_2__ bmiHeader; } ;
struct TYPE_8__ {int cColorBits; scalar_t__ iPixelType; } ;
struct TYPE_6__ {int /*<<< orphan*/  DBflag; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_4__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_BITFIELDS ; 
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int FALSE ; 
 scalar_t__ PFD_TYPE_COLORINDEX ; 
 scalar_t__ SetDIBitsToDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int WIDTH_BYTES_ALIGN32 (int /*<<< orphan*/ ,int) ; 

BOOL sw_SwapBuffers(HDC hdc, struct wgl_dc_data* dc_data)
{
    struct sw_framebuffer* fb = dc_data->sw_data;
    char Buffer[sizeof(BITMAPINFOHEADER) + 3 * sizeof(DWORD)];
    BITMAPINFO *bmi = (BITMAPINFO*)Buffer;
    BYTE Bpp = fb->pixel_format->cColorBits;

    if (!fb->gl_visual->DBflag)
        return TRUE;
    
    if (!fb->BackBuffer)
        return FALSE;

    bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
    bmi->bmiHeader.biBitCount = Bpp;
    bmi->bmiHeader.biClrImportant = 0;
    bmi->bmiHeader.biClrUsed = 0;
    bmi->bmiHeader.biPlanes = 1;
    bmi->bmiHeader.biSizeImage = WIDTH_BYTES_ALIGN32(fb->width, Bpp) * fb->height;
    bmi->bmiHeader.biXPelsPerMeter = 0;
    bmi->bmiHeader.biYPelsPerMeter = 0;
    bmi->bmiHeader.biHeight = fb->height;
    bmi->bmiHeader.biWidth = fb->width;
    bmi->bmiHeader.biCompression = Bpp == 16 ? BI_BITFIELDS : BI_RGB;

    if (Bpp == 16)
    {
        DWORD* BitMasks = (DWORD*)(&bmi->bmiColors[0]);
        BitMasks[0] = 0x0000F800;
        BitMasks[1] = 0x000007E0;
        BitMasks[2] = 0x0000001F;
    }

    return SetDIBitsToDevice(fb->Hdc, 0, 0, fb->width, fb->height, 0, 0, 0, fb->height, fb->BackBuffer, bmi,
            fb->pixel_format->iPixelType == PFD_TYPE_COLORINDEX ? DIB_PAL_COLORS : DIB_RGB_COLORS) != 0;
}