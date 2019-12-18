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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_3__ {scalar_t__ format; int /*<<< orphan*/  vlc_format; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ dxgi_format_t ;
typedef  scalar_t__ DXGI_FORMAT ;

/* Variables and functions */
 TYPE_1__* dxgi_formats ; 

vlc_fourcc_t DxgiFormatFourcc(DXGI_FORMAT format)
{
    for (const dxgi_format_t *f = dxgi_formats; f->name != NULL; ++f)
    {
        if (f->format == format)
            return f->vlc_format;
    }
    return 0;
}