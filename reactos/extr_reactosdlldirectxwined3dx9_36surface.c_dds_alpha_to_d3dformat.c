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
struct dds_pixel_format {int bpp; int amask; int /*<<< orphan*/  rmask; } ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_A8 ; 
 int /*<<< orphan*/  D3DFMT_UNKNOWN ; 
 int /*<<< orphan*/  WARN (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static D3DFORMAT dds_alpha_to_d3dformat(const struct dds_pixel_format *pixel_format)
{
    if (pixel_format->bpp == 8 && pixel_format->amask == 0xff)
        return D3DFMT_A8;

    WARN("Unknown Alpha pixel format (%u, %#x)\n", pixel_format->bpp, pixel_format->rmask);
    return D3DFMT_UNKNOWN;
}