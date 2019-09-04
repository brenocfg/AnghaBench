#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pixel_format_desc {scalar_t__ format; } ;
typedef  scalar_t__ D3DFORMAT ;

/* Variables and functions */
 scalar_t__ D3DFMT_UNKNOWN ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 
 struct pixel_format_desc const* formats ; 

const struct pixel_format_desc *get_format_info(D3DFORMAT format)
{
    unsigned int i = 0;
    while(formats[i].format != format && formats[i].format != D3DFMT_UNKNOWN) i++;
    if (formats[i].format == D3DFMT_UNKNOWN)
        FIXME("Unknown format %#x (as FOURCC %s).\n", format, debugstr_an((const char *)&format, 4));
    return &formats[i];
}