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
struct TYPE_3__ {int /*<<< orphan*/  d3dformat; int /*<<< orphan*/  wic_guid; } ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  D3DFMT_UNKNOWN ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_1__* wic_pixel_formats ; 

__attribute__((used)) static D3DFORMAT wic_guid_to_d3dformat(const GUID *guid)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(wic_pixel_formats); i++)
    {
        if (IsEqualGUID(wic_pixel_formats[i].wic_guid, guid))
            return wic_pixel_formats[i].d3dformat;
    }

    return D3DFMT_UNKNOWN;
}