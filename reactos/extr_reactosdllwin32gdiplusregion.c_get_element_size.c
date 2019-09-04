#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* right; TYPE_3__* left; } ;
struct TYPE_5__ {TYPE_2__ combine; int /*<<< orphan*/  path; } ;
struct TYPE_7__ {int type; TYPE_1__ elementdata; } ;
typedef  TYPE_3__ region_element ;
typedef  int INT ;
typedef  int /*<<< orphan*/  GpRect ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  RegionDataEmptyRect 131 
#define  RegionDataInfiniteRect 130 
#define  RegionDataPath 129 
#define  RegionDataRect 128 
 int write_path_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline INT get_element_size(const region_element* element)
{
    INT needed = sizeof(DWORD); /* DWORD for the type */
    switch(element->type)
    {
        case RegionDataRect:
            return needed + sizeof(GpRect);
        case RegionDataPath:
        {
            needed += write_path_data(element->elementdata.path, NULL);
            needed += sizeof(DWORD); /* Extra DWORD for path size */
            return needed;
        }
        case RegionDataEmptyRect:
        case RegionDataInfiniteRect:
            return needed;
        default:
            needed += get_element_size(element->elementdata.combine.left);
            needed += get_element_size(element->elementdata.combine.right);
            return needed;
    }

    return 0;
}