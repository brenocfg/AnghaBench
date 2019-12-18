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
struct TYPE_3__ {int i_rmask; int i_gmask; int i_bmask; } ;
typedef  TYPE_1__ video_format_t ;
typedef  scalar_t__ DXGI_FORMAT ;

/* Variables and functions */
 scalar_t__ DXGI_FORMAT_B8G8R8A8_UNORM ; 
 scalar_t__ DXGI_FORMAT_B8G8R8X8_UNORM ; 

void DxgiFormatMask(DXGI_FORMAT format, video_format_t *fmt)
{
    if (format == DXGI_FORMAT_B8G8R8X8_UNORM || format == DXGI_FORMAT_B8G8R8A8_UNORM)
    {
        fmt->i_rmask = 0x0000ff00;
        fmt->i_gmask = 0x00ff0000;
        fmt->i_bmask = 0xff000000;
    }
}