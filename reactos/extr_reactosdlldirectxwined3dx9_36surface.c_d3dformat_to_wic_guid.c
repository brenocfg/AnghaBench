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
struct TYPE_3__ {scalar_t__ d3dformat; int /*<<< orphan*/  const* wic_guid; } ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ D3DFORMAT ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* wic_pixel_formats ; 

__attribute__((used)) static const GUID *d3dformat_to_wic_guid(D3DFORMAT format)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(wic_pixel_formats); i++)
    {
        if (wic_pixel_formats[i].d3dformat == format)
            return wic_pixel_formats[i].wic_guid;
    }

    return NULL;
}