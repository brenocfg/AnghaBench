#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* n; } ;
typedef  TYPE_1__ cmsVEC3 ;
struct TYPE_7__ {int /*<<< orphan*/  u; int /*<<< orphan*/  a; } ;
typedef  TYPE_2__ cmsLine ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 size_t VX ; 
 size_t VY ; 
 size_t VZ ; 
 int /*<<< orphan*/  _cmsVEC3init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
void LineOf2Points(cmsContext ContextID, cmsLine* line, cmsVEC3* a, cmsVEC3* b)
{

    _cmsVEC3init(ContextID, &line ->a, a ->n[VX], a ->n[VY], a ->n[VZ]);
    _cmsVEC3init(ContextID, &line ->u, b ->n[VX] - a ->n[VX],
                            b ->n[VY] - a ->n[VY],
                            b ->n[VZ] - a ->n[VZ]);
}