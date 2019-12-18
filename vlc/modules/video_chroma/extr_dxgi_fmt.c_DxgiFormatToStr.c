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
struct TYPE_3__ {char const* name; scalar_t__ format; } ;
typedef  TYPE_1__ dxgi_format_t ;
typedef  scalar_t__ DXGI_FORMAT ;

/* Variables and functions */
 TYPE_1__* dxgi_formats ; 

const char *DxgiFormatToStr(DXGI_FORMAT format)
{
    for (const dxgi_format_t *f = dxgi_formats; f->name != NULL; ++f)
    {
        if (f->format == format)
            return f->name;
    }
    return NULL;
}