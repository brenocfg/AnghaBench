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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ drm; int present; scalar_t__ plane_id; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* fourccmatching ; 

__attribute__((used)) static void CheckFourCCList(uint32_t drmfourcc, uint32_t plane_id)
{
    unsigned i;

    for (i = 0; i < ARRAY_SIZE(fourccmatching); i++) {
        if (fourccmatching[i].drm == drmfourcc) {
            if (fourccmatching[i].present)
                /* this drmfourcc already has a plane_id found where it
                 * could be used, we'll stay with earlier findings.
                 */
                break;

            fourccmatching[i].present = true;
            fourccmatching[i].plane_id = plane_id;
            break;
        }
    }
}